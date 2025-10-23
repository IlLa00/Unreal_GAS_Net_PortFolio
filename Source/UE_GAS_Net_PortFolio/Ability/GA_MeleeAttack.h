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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee Attack")
	UAnimMontage* AttackMontage;

	UFUNCTION()
	void PerformAttack();

	void ApplyDamageToTarget(AActor* Target);
};
