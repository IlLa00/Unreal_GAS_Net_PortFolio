#include "Character/MyEnemy.h"
#include "Perception/AIPerceptionComponent.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet/MyAttributeSet.h"

AMyEnemy::AMyEnemy()
{
	PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComp"));

	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
	ASC->SetIsReplicated(true);
	ASC->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UMyAttributeSet>(TEXT("AttributeSet"));
}

UAbilitySystemComponent* AMyEnemy::GetAbilitySystemComponent() const
{
	return ASC;
}

void AMyEnemy::BeginPlay()
{
	Super::BeginPlay();

}

void AMyEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}