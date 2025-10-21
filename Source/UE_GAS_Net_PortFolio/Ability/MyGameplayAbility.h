// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "MyGameplayAbility.generated.h"

/**
 * 모든 Gameplay Ability의 베이스 클래스
 * MMORPG 스킬 시스템의 기반
 */
UCLASS()
class UE_GAS_NET_PORTFOLIO_API UMyGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UMyGameplayAbility();

	// ================================================================
	// Ability Info
	// ================================================================

	/** 스킬 이름 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	FText AbilityName;

	/** 스킬 설명 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	FText AbilityDescription;

	/** 스킬 아이콘 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	UTexture2D* AbilityIcon;

	/** 스킬 슬롯 (1~6번 키) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	int32 AbilitySlot = 0;

	/** 쿨다운 시간 (초) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	float CooldownDuration = 1.0f;

	/** 마나 코스트 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	float ManaCost = 0.0f;

	/** 스태미나 코스트 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	float StaminaCost = 0.0f;

	// ================================================================
	// Ability Activation
	// ================================================================

	/** Ability 활성화 */
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	/** Ability 종료 */
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	// ================================================================
	// Cost & Cooldown Check
	// ================================================================

	/** 코스트를 지불할 수 있는지 체크 */
	virtual bool CheckCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;

	/** 코스트 적용 */
	virtual void ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo) const override;

	/** 쿨다운 적용 */
	virtual void ApplyCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo) const;

	/** 남은 쿨다운 시간 가져오기 */
	UFUNCTION(BlueprintCallable, Category = "Ability")
	float GetCooldownTimeRemaining() const;

	// ================================================================
	// Target Handling
	// ================================================================

	/** 현재 타겟 가져오기 (PlayerController의 CurrentTarget) */
	UFUNCTION(BlueprintCallable, Category = "Ability")
	AActor* GetCurrentTarget() const;

	/** 타겟이 유효한지 체크 */
	UFUNCTION(BlueprintCallable, Category = "Ability")
	bool IsTargetValid(AActor* Target) const;

	/** 타겟과의 거리 */
	UFUNCTION(BlueprintCallable, Category = "Ability")
	float GetDistanceToTarget(AActor* Target) const;

protected:
	// ================================================================
	// Helper Functions
	// ================================================================

	/** Avatar Character 가져오기 */
	UFUNCTION(BlueprintCallable, Category = "Ability")
	ACharacter* GetAvatarCharacter() const;

	/** PlayerController 가져오기 */
	UFUNCTION(BlueprintCallable, Category = "Ability")
	class AMyPlayerController* GetMyPlayerController() const;

	/** AttributeSet 가져오기 */
	UFUNCTION(BlueprintCallable, Category = "Ability")
	class UMyAttributeSet* GetMyAttributeSet() const;
};
