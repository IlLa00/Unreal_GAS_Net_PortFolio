#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_WeaponCollision.generated.h"

UCLASS()
class UE_GAS_NET_PORTFOLIO_API UAnimNotify_WeaponCollision : public UAnimNotify
{
	GENERATED_BODY()

public:
	UAnimNotify_WeaponCollision();

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	// 충돌체를 활성화할지 비활성화할지 선택
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	bool bEnableCollision = true;
};
