#include "MyCharacterBase.h"

AMyCharacterBase::AMyCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMyCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMyCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

