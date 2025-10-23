#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "MyAIController.generated.h"

UCLASS()
class UE_GAS_NET_PORTFOLIO_API AMyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AMyAIController();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAIPerceptionComponent> PerceptionComp;

	UPROPERTY(EditAnywhere, Category = "IHGame")
	FName BBkey_CanSeePlayer;

	UPROPERTY(EditAnywhere, Category = "IHGame")
	FName BBkey_Player;
};
