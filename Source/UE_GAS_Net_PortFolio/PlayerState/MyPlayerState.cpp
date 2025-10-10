#include "MyPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "AbilitySystemComponent.h"

AMyPlayerState::AMyPlayerState()
{
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));

	NetUpdateFrequency = 100.0f; // PlayerState 기본값이 낮아서 GAS에 부족할 수 있음.
}

UAbilitySystemComponent* AMyPlayerState::GetAbilitySystemComponent() const
{
	return ASC;
}

void AMyPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyPlayerState, ASC);
}

