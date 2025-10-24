#pragma once

#include "CoreMinimal.h"
#include "Character/MyPlayer.h"
#include "AuroraPlayer.generated.h"

/**
 * Aurora - 근접 무기(칼)를 사용하는 플레이어 캐릭터
 */
UCLASS()
class UE_GAS_NET_PORTFOLIO_API AAuroraPlayer : public AMyPlayer
{
	GENERATED_BODY()

public:
	AAuroraPlayer();

public:
	// 근접 무기 컴포넌트 (칼)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	class UMeleeWeaponComponent* MeleeWeapon;
};
