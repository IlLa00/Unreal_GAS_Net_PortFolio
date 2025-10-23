#include "MyPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet/MyAttributeSet.h"
#include "Ability/MyGameplayAbility.h"

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

void AMyPlayerState::GrantAbilities()
{
	if (!ASC)
		return;

	if (GetLocalRole() != ROLE_Authority)
		return;

	RemoveAbilities();

	for (TSubclassOf<UMyGameplayAbility> AbilityClass : DefaultAbilities)
	{
		if (!AbilityClass)
			continue;

		FGameplayAbilitySpec AbilitySpec(AbilityClass, 1, INDEX_NONE, this);
		FGameplayAbilitySpecHandle Handle = ASC->GiveAbility(AbilitySpec);
		GrantedAbilityHandles.Add(Handle);

		UE_LOG(LogTemp, Log, TEXT("Granted Ability: %s"), *AbilityClass->GetName());
	}
}

void AMyPlayerState::RemoveAbilities()
{
	if (!ASC)
		return;

	if (GetLocalRole() != ROLE_Authority)
		return;

	for (FGameplayAbilitySpecHandle Handle : GrantedAbilityHandles)
		ASC->ClearAbility(Handle);

	GrantedAbilityHandles.Empty();
}

