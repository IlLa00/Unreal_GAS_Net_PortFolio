#include "Character/MyPlayer.h"
#include "PlayerState/MyPlayerState.h"
#include "Controller/MyPlayerController.h"
#include "Character/MyEnemy.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystemComponent.h"
#include "Kismet/KismetMathLibrary.h"

AMyPlayer::AMyPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->SocketOffset = FVector(0, 70, 90);
	SpringArmComp->TargetArmLength = 300;
	SpringArmComp->bUsePawnControlRotation = true;

	CamComp = CreateDefaultSubobject<UCameraComponent>(TEXT("TpsCamComp"));
	CamComp->SetupAttachment(SpringArmComp);
	CamComp->bUsePawnControlRotation = false;

	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = 600.0f; // Default walk speed

	SetReplicates(true);
}

void AMyPlayer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void AMyPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AMyPlayerState* State = Cast<AMyPlayerState>(GetPlayerState());
	if (!State) return;

	if (!State->GetAbilitySystemComponent()) return;

	State->GetAbilitySystemComponent()->InitAbilityActorInfo(State, this);

	// Ability 부여 (서버)
	State->GrantAbilities();
}

void AMyPlayer::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	AMyPlayerState* State = Cast<AMyPlayerState>(GetPlayerState());
	if (!State) return;

	if (!State->GetAbilitySystemComponent()) return;

	State->GetAbilitySystemComponent()->InitAbilityActorInfo(State, this);
}

void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();

}

void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 타겟 락온 카메라 회전
	AMyPlayerController* PC = Cast<AMyPlayerController>(GetController());
	if (PC && PC->CurrentTarget)
	{
		// 타겟이 유효한지 체크 (죽었거나 너무 멀면 타겟 해제)
		if (!IsValid(PC->CurrentTarget) || PC->CurrentTarget->IsPendingKillPending())
		{
			PC->ClearTarget();
			return;
		}

		// 타겟과의 거리 체크
		float Distance = FVector::Dist(GetActorLocation(), PC->CurrentTarget->GetActorLocation());
		if (Distance > 5000.0f) // 50m 이상 떨어지면 타겟 해제
		{
			PC->ClearTarget();
			return;
		}

		// 타겟 방향 계산
		FVector TargetLocation = PC->CurrentTarget->GetActorLocation();
		FVector MyLocation = GetActorLocation();
		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(MyLocation, TargetLocation);

		// 컨트롤러 회전을 타겟 방향으로 부드럽게 보간
		FRotator CurrentRotation = GetControlRotation();
		FRotator NewRotation = FMath::RInterpTo(CurrentRotation, LookAtRotation, DeltaTime, 10.0f);

		// Pitch만 제한 (너무 위아래로 보지 않도록)
		NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch, -45.0f, 45.0f);

		PC->SetControlRotation(NewRotation);

		// 캐릭터도 타겟 방향으로 부드럽게 회전 (Yaw만)
		FRotator CharacterRotation = GetActorRotation();
		FRotator TargetCharacterRotation = FRotator(0.0f, LookAtRotation.Yaw, 0.0f);
		FRotator NewCharacterRotation = FMath::RInterpTo(CharacterRotation, TargetCharacterRotation, DeltaTime, 8.0f);
		SetActorRotation(NewCharacterRotation);
	}
}

void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}