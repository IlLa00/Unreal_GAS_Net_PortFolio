#include "Weapon/WeaponComponent.h"

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bIsEquipped = false;
}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UWeaponComponent::Attack()
{
	// 자식 클래스에서 구현
}

void UWeaponComponent::Equip()
{
	bIsEquipped = true;
}

void UWeaponComponent::Unequip()
{
	bIsEquipped = false;
}
