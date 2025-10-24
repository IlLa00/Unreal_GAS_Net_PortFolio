#include "Character/AuroraPlayer.h"
#include "Weapon/MeleeWeaponComponent.h"
#include "Components/CapsuleComponent.h"

AAuroraPlayer::AAuroraPlayer()
{
	// 근접 무기 컴포넌트 생성
	MeleeWeapon = CreateDefaultSubobject<UMeleeWeaponComponent>(TEXT("MeleeWeapon"));
	MeleeWeapon->HitCapsule->SetupAttachment(GetMesh(), TEXT("weapon")); // 메시의 WeaponSocket에 부착

	// 필요시 Aurora 전용 설정 추가
	// 예: 이동 속도, 공격력 등
}
