#include "Character/MyBoss.h"
#include "Controller/MyAIController.h"

AMyBoss::AMyBoss()
{
	AIControllerClass = AMyAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	bReplicates = true;
}

void AMyBoss::BeginPlay()
{
	Super::BeginPlay();

}

void AMyBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}