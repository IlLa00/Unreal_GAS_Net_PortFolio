// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability/MyGameplayAbility.h"
#include "GA_MeleeAttack.generated.h"

/**
 * 근접 공격 스킬
 * MMORPG의 기본 공격
 */
UCLASS()
class UE_GAS_NET_PORTFOLIO_API UGA_MeleeAttack : public UMyGameplayAbility
{
	GENERATED_BODY()

public:
	UGA_MeleeAttack();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:
	/** 공격 범위 (cm) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee Attack")
	float AttackRange = 200.0f;

	/** 기본 데미지 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee Attack")
	float BaseDamage = 10.0f;

	/** 공격 애니메이션 몽타주 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee Attack")
	UAnimMontage* AttackMontage;

	/** 실제 공격 실행 */
	UFUNCTION()
	void PerformAttack();

	/** 데미지 적용 */
	void ApplyDamageToTarget(AActor* Target);
};
