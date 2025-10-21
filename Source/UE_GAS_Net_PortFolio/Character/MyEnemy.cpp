#include "Character/MyEnemy.h"
#include "Perception/AIPerceptionComponent.h"

AMyEnemy::AMyEnemy()
{
	PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComp"));
}
