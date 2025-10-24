#pragma once

#include "CoreMinimal.h"
#include "Ability/MyGameplayAbility.h"
#include "GA_MeleeAttack.generated.h"

UCLASS()
class UE_GAS_NET_PORTFOLIO_API UGA_MeleeAttack : public UMyGameplayAbility
{
	GENERATED_BODY()

public:
	UGA_MeleeAttack();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee Attack")
	float AttackRange = 200.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee Attack")
	float BaseDamage = 10.0f;

	// 콤보 시스템
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combo")
	TArray<UAnimMontage*> ComboMontages;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combo")
	float ComboResetTime = 1.5f; // 콤보 초기화 시간

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combo")
	int32 MaxComboCount = 3; // 최대 콤보 수

	UFUNCTION()
	void PerformAttack();

	void ApplyDamageToTarget(AActor* Target);

private:
	// 콤보 관련 변수
	int32 CurrentComboCount = 0;
	FTimerHandle ComboResetTimerHandle;

	void ResetCombo();
	void PlayComboMontage();
};
