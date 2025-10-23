#include "Ability/GA_MeleeAttack.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/Character.h"
#include "Controller/MyPlayerController.h"
#include "AttributeSet/MyAttributeSet.h"
#include "Character/MyEnemy.h"
#include "Kismet/GameplayStatics.h"

UGA_MeleeAttack::UGA_MeleeAttack()
{
	AbilityName = FText::FromString(TEXT("Melee Attack"));
	AbilityDescription = FText::FromString(TEXT("Basic melee attack"));
	AbilitySlot = 1; // 1번 키

	CooldownDuration = 1.0f;
	StaminaCost = 10.0f;

	AttackRange = 200.0f; 
	BaseDamage = 10.0f;
}

void UGA_MeleeAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	AActor* Target = GetCurrentTarget();
	if (!IsTargetValid(Target))
	{
		UE_LOG(LogTemp, Warning, TEXT("No valid target for Melee Attack"));
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	float DistanceToTarget = GetDistanceToTarget(Target);
	if (DistanceToTarget > AttackRange)
	{
		UE_LOG(LogTemp, Warning, TEXT("Target too far: %.2f cm (max: %.2f cm)"), DistanceToTarget, AttackRange);
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	ACharacter* Character = GetAvatarCharacter();
	if (Character && AttackMontage)
		Character->PlayAnimMontage(AttackMontage);

	PerformAttack();

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}

void UGA_MeleeAttack::PerformAttack()
{
	AActor* Target = GetCurrentTarget();
	if (!Target)
		return;

	ApplyDamageToTarget(Target);

	UE_LOG(LogTemp, Log, TEXT("Melee Attack hit %s for %.2f damage"), *Target->GetName(), BaseDamage);
}

void UGA_MeleeAttack::ApplyDamageToTarget(AActor* Target)
{
	if (!Target)
		return;

	AMyEnemy* Enemy = Cast<AMyEnemy>(Target);
	if (!Enemy)
		return;

	// TODO: GameplayEffect로 데미지 적용
	// 지금은 간단하게 직접 데미지 적용

	UAbilitySystemComponent* TargetASC = Enemy->GetAbilitySystemComponent();
	if (!TargetASC)
	{
		ACharacter* AvatarChar = GetAvatarCharacter();
		if (AvatarChar)
			UGameplayStatics::ApplyDamage(Enemy, BaseDamage, AvatarChar->GetController(), AvatarChar, UDamageType::StaticClass());
		
		return;
	}

	UMyAttributeSet* TargetAttributeSet = const_cast<UMyAttributeSet*>(TargetASC->GetSet<UMyAttributeSet>());
	if (TargetAttributeSet)
	{
		UMyAttributeSet* MyAttributeSet = GetMyAttributeSet();
		float FinalDamage = BaseDamage;

		if (MyAttributeSet)
			FinalDamage += MyAttributeSet->GetAttackPower();

		FinalDamage -= TargetAttributeSet->GetDefense();
		FinalDamage = FMath::Max(FinalDamage, 1.0f);

		float NewHealth = TargetAttributeSet->GetHealth() - FinalDamage;
		TargetAttributeSet->SetHealth(NewHealth);

		UE_LOG(LogTemp, Log, TEXT("Dealt %.2f damage to %s (HP: %.2f)"), FinalDamage, *Enemy->GetName(), NewHealth);
	}
}
