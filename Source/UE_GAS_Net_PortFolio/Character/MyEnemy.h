#pragma once

#include "CoreMinimal.h"
#include "Character/MyCharacterBase.h"
#include "MyEnemy.generated.h"

UCLASS()
class UE_GAS_NET_PORTFOLIO_API AMyEnemy : public AMyCharacterBase
{
	GENERATED_BODY()

public:
	AMyEnemy();

public:
	FORCEINLINE class AMyPlayer* GetTarget() { return Target; }

private:
	UPROPERTY(VisibleAnywhere, Category = "AI")
	TObjectPtr<class UAIPerceptionComponent> PerceptionComp;

	TObjectPtr<class AMyPlayer> Target;
	
};
