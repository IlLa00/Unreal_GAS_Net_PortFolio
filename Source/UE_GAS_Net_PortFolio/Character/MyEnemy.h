#pragma once

#include "CoreMinimal.h"
#include "Character/MyCharacterBase.h"
#include "AbilitySystemInterface.h"
#include "MyEnemy.generated.h"

UCLASS()
class UE_GAS_NET_PORTFOLIO_API AMyEnemy : public AMyCharacterBase, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AMyEnemy();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

public:
	FORCEINLINE class AMyPlayer* GetTarget() { return Target; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	TObjectPtr<UAbilitySystemComponent> ASC;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	TObjectPtr<class UMyAttributeSet> AttributeSet;

	UPROPERTY(VisibleAnywhere, Category = "AI")
	TObjectPtr<class UAIPerceptionComponent> PerceptionComp;

	TObjectPtr<class AMyPlayer> Target;
};
