#include "AnimNotify/AnimNotify_WeaponCollision.h"
#include "Weapon/MeleeWeaponComponent.h"
#include "GameFramework/Character.h"

UAnimNotify_WeaponCollision::UAnimNotify_WeaponCollision()
{
#if WITH_EDITORONLY_DATA
	NotifyColor = FColor(255, 200, 100, 255); // 주황색
#endif
}

void UAnimNotify_WeaponCollision::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (!MeshComp) return;

	ACharacter* Character = Cast<ACharacter>(MeshComp->GetOwner());
	if (!Character) return;

	// 캐릭터에게 부착된 MeleeWeaponComponent 찾기
	UMeleeWeaponComponent* WeaponComp = Character->FindComponentByClass<UMeleeWeaponComponent>();
	if (!WeaponComp) return;

	// 충돌체 활성화/비활성화
	if (bEnableCollision)
	{
		WeaponComp->EnableCollision();
	}
	else
	{
		WeaponComp->DisableCollision();
	}
}
