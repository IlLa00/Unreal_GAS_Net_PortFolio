#pragma once

#include "CoreMinimal.h"
#include "Character/MyEnemy.h"
#include "MyBoss.generated.h"

UCLASS()
class UE_GAS_NET_PORTFOLIO_API AMyBoss : public AMyEnemy
{
	GENERATED_BODY()
	
public:
	AMyBoss();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
