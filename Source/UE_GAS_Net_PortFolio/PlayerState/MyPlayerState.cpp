#include "MyPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet/MyAttributeSet.h"

AMyPlayerState::AMyPlayerState()
{
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
	ASC->SetIsReplicated(true);
	ASC->SetReplicationMode(EGameplayEffectReplicationMode::Mixed); 

	AttributeSet = CreateDefaultSubobject<UMyAttributeSet>(TEXT("AttributeSet"));

	// PlayerState 기본값이 낮아서 GAS에 부족할 수 있음.
	NetUpdateFrequency = 100.0f;
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

