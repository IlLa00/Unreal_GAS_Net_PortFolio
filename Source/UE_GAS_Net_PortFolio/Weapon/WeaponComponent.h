#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "WeaponComponent.generated.h"

UCLASS(Abstract, Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UE_GAS_NET_PORTFOLIO_API UWeaponComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	UWeaponComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// 무기별로 구현할 공격 함수
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void Attack();

	// 활성화/비활성화
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void Equip();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void Unequip();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	bool bIsEquipped;
};
