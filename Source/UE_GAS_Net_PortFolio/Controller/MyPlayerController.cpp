#include "Controller/MyPlayerController.h"
#include "Net/UnrealNetwork.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Character/MyEnemy.h"
#include "Ability/MyGameplayAbility.h"

AMyPlayerController::AMyPlayerController()
{
	bReplicates = true;
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (DefaultMappingContext)
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		if (MoveAction)
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyPlayerController::OnMove);

		if (LookAction)
			EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyPlayerController::OnLook);

		if (JumpAction)
		{
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AMyPlayerController::OnJumpStarted);
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AMyPlayerController::OnJumpCompleted);
		}

		if (SprintAction)
		{
			EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &AMyPlayerController::OnSprintStarted);
			EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AMyPlayerController::OnSprintCompleted);
		}

		if (TargetToggleAction)
			EnhancedInputComponent->BindAction(TargetToggleAction, ETriggerEvent::Triggered, this, &AMyPlayerController::OnTargetToggle);

		if (Ability1Action)
			EnhancedInputComponent->BindAction(Ability1Action, ETriggerEvent::Triggered, this, &AMyPlayerController::OnAbility1);
		if (Ability2Action)
			EnhancedInputComponent->BindAction(Ability2Action, ETriggerEvent::Triggered, this, &AMyPlayerController::OnAbility2);
		if (Ability3Action)
			EnhancedInputComponent->BindAction(Ability3Action, ETriggerEvent::Triggered, this, &AMyPlayerController::OnAbility3);
		if (Ability4Action)
			EnhancedInputComponent->BindAction(Ability4Action, ETriggerEvent::Triggered, this, &AMyPlayerController::OnAbility4);
		if (Ability5Action)
			EnhancedInputComponent->BindAction(Ability5Action, ETriggerEvent::Triggered, this, &AMyPlayerController::OnAbility5);
		if (Ability6Action)
			EnhancedInputComponent->BindAction(Ability6Action, ETriggerEvent::Triggered, this, &AMyPlayerController::OnAbility6);
	}
}

void AMyPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyPlayerController, CurrentTarget);
}

void AMyPlayerController::ToggleTargetSelection()
{
	// 타겟이 이미 있으면 해제 (토글)
	if (CurrentTarget)
	{
		ClearTarget();
		return;
	}

	// 타겟이 없으면 가장 가까운 적을 찾아서 설정
	AMyEnemy* NewTarget = FindNearestEnemy();
	if (NewTarget)
	{
		Server_SetTarget(NewTarget);
	}
}

void AMyPlayerController::ClearTarget()
{
	Server_SetTarget(nullptr);
}

void AMyPlayerController::Server_SetTarget_Implementation(AMyEnemy* NewTarget)
{
	CurrentTarget = NewTarget;

	// 서버에서도 회전 모드 변경 (OnRep은 클라이언트에서만 호출됨)
	OnRep_CurrentTarget();
}

AMyEnemy* AMyPlayerController::FindNearestEnemy()
{
	APawn* MyPawn = GetPawn();
	if (!MyPawn)
		return nullptr;

	FVector MyLocation = MyPawn->GetActorLocation();
	FVector MyForward = MyPawn->GetActorForwardVector();

	TArray<AActor*> FoundActors;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(MyPawn);

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

	UKismetSystemLibrary::SphereOverlapActors(
		GetWorld(),
		MyLocation,
		MaxTargetDistance,
		ObjectTypes,
		nullptr,
		ActorsToIgnore,
		FoundActors
	);

	AMyEnemy* NearestEnemy = nullptr;
	float NearestDistance = MaxTargetDistance + 1.0f;

	for (AActor* Actor : FoundActors)
	{
		AMyEnemy* Enemy = Cast<AMyEnemy>(Actor);
		if (!Enemy) continue;

		FVector ToTarget = Enemy->GetActorLocation() - MyLocation;
		float Distance = ToTarget.Size();

		// 시야각 체크 (전방 180도)
		ToTarget.Normalize();
		float DotProduct = FVector::DotProduct(MyForward, ToTarget);
		float AngleDegrees = FMath::RadiansToDegrees(FMath::Acos(DotProduct));

		if (AngleDegrees > TargetingFOV / 2.0f)
			continue;

		// 더 가까운 타겟 선택
		if (Distance < NearestDistance)
		{
			NearestDistance = Distance;
			NearestEnemy = Enemy;
		}
	}

	return NearestEnemy;
}

void AMyPlayerController::OnRep_CurrentTarget()
{
	// 타겟이 변경되면 UI 업데이트
	// TODO: UI 위젯에 이벤트 전달

	// 캐릭터 회전 모드 변경
	if (ACharacter* character = Cast<ACharacter>(GetPawn()))
	{
		if (UCharacterMovementComponent* MovementComp = character->GetCharacterMovement())
		{
			if (CurrentTarget)
			{
				// 타겟이 있으면 이동 방향으로 회전하지 않음 (카메라 방향 유지)
				MovementComp->bOrientRotationToMovement = false;
				MovementComp->bUseControllerDesiredRotation = false;
			}
			else
			{
				// 타겟이 없으면 이동 방향으로 회전
				MovementComp->bOrientRotationToMovement = true;
				MovementComp->bUseControllerDesiredRotation = false;
			}
		}
	}
}

void AMyPlayerController::OnTargetToggle()
{
	ToggleTargetSelection();
}

void AMyPlayerController::OnMove(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (APawn* ControlledPawn = GetPawn())
	{
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		ControlledPawn->AddMovementInput(ForwardDirection, MovementVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AMyPlayerController::OnLook(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddYawInput(-1.0f * LookAxisVector.X);
	AddPitchInput(LookAxisVector.Y);
}

void AMyPlayerController::OnJumpStarted()
{
	if (ACharacter* ControlledCharacter = Cast<ACharacter>(GetPawn()))
		ControlledCharacter->Jump();
}

void AMyPlayerController::OnJumpCompleted()
{
	if (ACharacter* ControlledCharacter = Cast<ACharacter>(GetPawn()))
		ControlledCharacter->StopJumping();
}

void AMyPlayerController::OnSprintStarted()
{
	if (ACharacter* ControlledCharacter = Cast<ACharacter>(GetPawn()))
	{
		if (UCharacterMovementComponent* MovementComp = ControlledCharacter->GetCharacterMovement())
			MovementComp->MaxWalkSpeed = 1000.0f; // Sprint Speed
	}
}

void AMyPlayerController::OnSprintCompleted()
{
	if (ACharacter* ControlledCharacter = Cast<ACharacter>(GetPawn()))
	{
		if (UCharacterMovementComponent* MovementComp = ControlledCharacter->GetCharacterMovement())
			MovementComp->MaxWalkSpeed = 600.0f; // Walk Speed
	}
}

UAbilitySystemComponent* AMyPlayerController::GetASC()
{
	if (IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(PlayerState))
		return ASI->GetAbilitySystemComponent();

	return nullptr;
}

// ================================================================
// Ability Activation
// ================================================================

void AMyPlayerController::OnAbility1()
{
	ActivateAbilityBySlot(1);
}

void AMyPlayerController::OnAbility2()
{
	ActivateAbilityBySlot(2);
}

void AMyPlayerController::OnAbility3()
{
	ActivateAbilityBySlot(3);
}

void AMyPlayerController::OnAbility4()
{
	ActivateAbilityBySlot(4);
}

void AMyPlayerController::OnAbility5()
{
	ActivateAbilityBySlot(5);
}

void AMyPlayerController::OnAbility6()
{
	ActivateAbilityBySlot(6);
}

void AMyPlayerController::ActivateAbilityBySlot(int32 SlotNumber)
{
	UAbilitySystemComponent* ASC = GetASC();
	if (!ASC)
	{
		UE_LOG(LogTemp, Warning, TEXT("No ASC found"));
		return;
	}

	// 활성화 가능한 Ability 찾기
	TArray<FGameplayAbilitySpec> ActivatableAbilities = ASC->GetActivatableAbilities();

	for (const FGameplayAbilitySpec& Spec : ActivatableAbilities)
	{
		UMyGameplayAbility* MyAbility = Cast<UMyGameplayAbility>(Spec.Ability);
		if (!MyAbility)
			continue;

		// 슬롯 번호가 일치하는 Ability 찾기
		if (MyAbility->AbilitySlot == SlotNumber)
		{
			// Ability 활성화
			bool bSuccess = ASC->TryActivateAbility(Spec.Handle);

			if (bSuccess)
			{
				UE_LOG(LogTemp, Log, TEXT("Activated Ability: %s (Slot %d)"), *MyAbility->AbilityName.ToString(), SlotNumber);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Failed to activate Ability: %s (Slot %d)"), *MyAbility->AbilityName.ToString(), SlotNumber);
			}

			return;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("No Ability found in slot %d"), SlotNumber);
}
