// Fill out your copyright notice in the Description page of Project Settings.

#include "Ability/MyGameplayAbility.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/Character.h"
#include "Controller/MyPlayerController.h"
#include "PlayerState/MyPlayerState.h"
#include "AttributeSet/MyAttributeSet.h"
#include "Character/MyEnemy.h"

UMyGameplayAbility::UMyGameplayAbility()
{
	// 기본 설정
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;

	// 기본값
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

// ================================================================
// Cost & Cooldown
// ================================================================

bool UMyGameplayAbility::CheckCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CheckCost(Handle, ActorInfo, OptionalRelevantTags))
		return false;

	UMyAttributeSet* AttributeSet = GetMyAttributeSet();
	if (!AttributeSet)
		return false;

	// 마나 체크
	if (ManaCost > 0.0f && AttributeSet->GetMana() < ManaCost)
		return false;

	// 스태미나 체크
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

	// 마나 소모
	if (ManaCost > 0.0f)
	{
		const_cast<UMyAttributeSet*>(AttributeSet)->SetMana(AttributeSet->GetMana() - ManaCost);
	}

	// 스태미나 소모
	if (StaminaCost > 0.0f)
	{
		const_cast<UMyAttributeSet*>(AttributeSet)->SetStamina(AttributeSet->GetStamina() - StaminaCost);
	}
}

void UMyGameplayAbility::ApplyCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo) const
{
	// TODO: GameplayEffect로 쿨다운 적용
	// 지금은 간단하게 구현, 나중에 GE_Cooldown으로 대체
}

float UMyGameplayAbility::GetCooldownTimeRemaining() const
{
	// TODO: 실제 쿨다운 시간 계산
	return 0.0f;
}

// ================================================================
// Target Handling
// ================================================================

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

	// 타겟이 살아있는지
	if (Target->IsPendingKillPending())
		return false;

	// Enemy 타입인지
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

// ================================================================
// Helper Functions
// ================================================================

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
