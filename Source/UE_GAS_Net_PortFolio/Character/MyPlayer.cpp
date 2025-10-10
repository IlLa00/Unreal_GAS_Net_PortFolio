#include "Character/MyPlayer.h"
#include "PlayerState/MyPlayerState.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "AbilitySystemComponent.h"

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

	bUseControllerRotationYaw = true;

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
}