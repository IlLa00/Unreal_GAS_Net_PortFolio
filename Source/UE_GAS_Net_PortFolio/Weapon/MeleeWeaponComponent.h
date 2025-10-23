#pragma once

#include "CoreMinimal.h"
#include "Weapon/WeaponComponent.h"
#include "MeleeWeaponComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UE_GAS_NET_PORTFOLIO_API UMeleeWeaponComponent : public UWeaponComponent
{
	GENERATED_BODY()

public:
	UMeleeWeaponComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Attack() override;
	virtual void Equip() override;
	virtual void Unequip() override;

	// 히트 판정을 위한 캡슐 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon|Melee")
	class UCapsuleComponent* HitCapsule;

	// 캡슐 크기 설정 (블루프린트에서 조정 가능)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Melee")
	float CapsuleRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Melee")
	float CapsuleHalfHeight;

protected:
	// 충돌 이벤트
	UFUNCTION()
	void OnHitCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	// 공격 중 여부
	bool bIsAttacking;
};
