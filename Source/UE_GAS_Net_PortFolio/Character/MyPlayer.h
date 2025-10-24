#pragma once

#include "CoreMinimal.h"
#include "Character/MyCharacterBase.h"
#include "MyPlayer.generated.h"

UCLASS()
class UE_GAS_NET_PORTFOLIO_API AMyPlayer : public AMyCharacterBase
{
	GENERATED_BODY()

public:
	AMyPlayer();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

public:
	UPROPERTY(EditAnywhere, Category = "Camera")
	class USpringArmComponent* SpringArmComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	class UCameraComponent* CamComp;
};
