#include "Ability/MyGameplayAbility.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/Character.h"
#include "Controller/MyPlayerController.h"
#include "PlayerState/MyPlayerState.h"
#include "AttributeSet/MyAttributeSet.h"
#include "Character/MyEnemy.h"

UMyGameplayAbility::UMyGameplayAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;

	AbilityName = FText::FromString("Ability");
	AbilityDescription = FText::FromString("Ability Description");
	AbilitySlot = 0;
	CooldownDuration = 1.0f;
	ManaCost = 0.0f;
	StaminaCost = 0.0f;
}

void UMyGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UMyGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

bool UMyGameplayAbility::CheckCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CheckCost(Handle, ActorInfo, OptionalRelevantTags))
		return false;

	UMyAttributeSet* AttributeSet = GetMyAttributeSet();
	if (!AttributeSet)
		return false;

	if (ManaCost > 0.0f && AttributeSet->GetMana() < ManaCost)
		return false;

	if (StaminaCost > 0.0f && AttributeSet->GetStamina() < StaminaCost)
		return false;

	return true;
}

void UMyGameplayAbility::ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo) const
{
	Super::ApplyCost(Handle, ActorInfo, ActivationInfo);

	UMyAttributeSet* AttributeSet = GetMyAttributeSet();
	if (!AttributeSet)
		return;

	if (ManaCost > 0.0f)
		const_cast<UMyAttributeSet*>(AttributeSet)->SetMana(AttributeSet->GetMana() - ManaCost);

	if (StaminaCost > 0.0f)
		const_cast<UMyAttributeSet*>(AttributeSet)->SetStamina(AttributeSet->GetStamina() - StaminaCost);
}

void UMyGameplayAbility::ApplyCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo) const
{
	// TODO: GameplayEffect로 쿨다운 적용
	// 지금은 간단하게 구현, 나중에 GE_Cooldown으로 대체
}

AActor* UMyGameplayAbility::GetCurrentTarget() const
{
	AMyPlayerController* PC = GetMyPlayerController();
	if (!PC)
		return nullptr;

	return PC->CurrentTarget;
}

bool UMyGameplayAbility::IsTargetValid(AActor* Target) const
{
	if (!Target)
		return false;

	if (Target->IsPendingKillPending())
		return false;

	AMyEnemy* Enemy = Cast<AMyEnemy>(Target);
	if (!Enemy)
		return false;

	// TODO: 체력이 0 이상인지 체크

	return true;
}

float UMyGameplayAbility::GetDistanceToTarget(AActor* Target) const
{
	if (!Target)
		return -1.0f;

	ACharacter* AvatarChar = GetAvatarCharacter();
	if (!AvatarChar)
		return -1.0f;

	return FVector::Dist(AvatarChar->GetActorLocation(), Target->GetActorLocation());
}

ACharacter* UMyGameplayAbility::GetAvatarCharacter() const
{
	return Cast<ACharacter>(GetAvatarActorFromActorInfo());
}

AMyPlayerController* UMyGameplayAbility::GetMyPlayerController() const
{
	if (const FGameplayAbilityActorInfo* ActorInfo = GetCurrentActorInfo())
	{
		return Cast<AMyPlayerController>(ActorInfo->PlayerController.Get());
	}
	return nullptr;
}

UMyAttributeSet* UMyGameplayAbility::GetMyAttributeSet() const
{
	if (UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo())
	{
		return const_cast<UMyAttributeSet*>(ASC->GetSet<UMyAttributeSet>());
	}
	return nullptr;
}
