#include "Weapon/MeleeWeaponComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"

UMeleeWeaponComponent::UMeleeWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// 캡슐 컴포넌트 생성
	HitCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("HitCapsule"));
	HitCapsule->SetupAttachment(this); // WeaponComponent의 자식으로 부착
	HitCapsule->SetCapsuleSize(CapsuleRadius, CapsuleHalfHeight);

	// 초기에는 충돌 비활성화 (공격할 때만 활성화)
	HitCapsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	HitCapsule->SetCollisionResponseToAllChannels(ECR_Ignore);
	HitCapsule->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	bIsAttacking = false;
}

void UMeleeWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	// 충돌 이벤트 바인딩
	if(HitCapsule)
		HitCapsule->OnComponentBeginOverlap.AddDynamic(this, &UMeleeWeaponComponent::OnHitCapsuleBeginOverlap);
}

void UMeleeWeaponComponent::Attack()
{
	Super::Attack();

	if (!bIsEquipped) return;

	// 공격 시작 - 충돌 활성화
	bIsAttacking = true;
	HitCapsule->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	// TODO: 나중에 타이머로 공격 시간 후 자동으로 비활성화
	// GetWorld()->GetTimerManager().SetTimer(...);
}

void UMeleeWeaponComponent::Equip()
{
	Super::Equip();

	// 장착 시 캡슐을 보이게 설정 (디버깅용)
	HitCapsule->SetHiddenInGame(false);
}

void UMeleeWeaponComponent::Unequip()
{
	Super::Unequip();

	// 해제 시 충돌 비활성화
	bIsAttacking = false;
	HitCapsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	HitCapsule->SetHiddenInGame(true);
}

void UMeleeWeaponComponent::EnableCollision()
{
	if (!HitCapsule) return;

	// 충돌 활성화
	bIsAttacking = true;
	HitCapsule->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	// 피격 액터 리스트 초기화 (새로운 공격 시작)
	HitActors.Empty();

	UE_LOG(LogTemp, Log, TEXT("MeleeWeapon Collision Enabled"));
}

void UMeleeWeaponComponent::DisableCollision()
{
	if (!HitCapsule) return;

	// 충돌 비활성화
	bIsAttacking = false;
	HitCapsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	UE_LOG(LogTemp, Log, TEXT("MeleeWeapon Collision Disabled"));
}

void UMeleeWeaponComponent::OnHitCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bIsAttacking) return;
	if (!OtherActor || OtherActor == GetOwner()) return;

	// 이미 피격한 액터는 무시 (중복 피격 방지)
	if (HitActors.Contains(OtherActor)) return;

	// 피격 액터 추가
	HitActors.Add(OtherActor);

	UE_LOG(LogTemp, Log, TEXT("MeleeWeapon Hit: %s"), *OtherActor->GetName());

	// TODO: 데미지 처리 로직
	// GAS의 GameplayEffect를 사용하여 데미지 적용
}
