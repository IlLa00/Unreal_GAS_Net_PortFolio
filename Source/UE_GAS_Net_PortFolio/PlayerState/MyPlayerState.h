#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "MyPlayerState.generated.h"

class UMyAttributeSet;
class UMyGameplayAbility;

UCLASS()
class UE_GAS_NET_PORTFOLIO_API AMyPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AMyPlayerState();

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable, Category = "GAS")
	UMyAttributeSet* GetAttributeSet() const { return AttributeSet; }

	// ================================================================
	// Ability Management
	// ================================================================

	/** 시작 시 부여할 Ability 리스트 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	TArray<TSubclassOf<UMyGameplayAbility>> DefaultAbilities;

	/** Ability 부여 */
	void GrantAbilities();

	/** Ability 제거 */
	void RemoveAbilities();

	/** 부여된 Ability Handle 저장 */
	UPROPERTY()
	TArray<FGameplayAbilitySpecHandle> GrantedAbilityHandles;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated, Category = "GAS")
	TObjectPtr<UAbilitySystemComponent> ASC;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	TObjectPtr<UMyAttributeSet> AttributeSet;
};
