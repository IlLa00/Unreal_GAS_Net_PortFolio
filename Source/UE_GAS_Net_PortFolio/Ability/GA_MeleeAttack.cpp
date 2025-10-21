// Fill out your copyright notice in the Description page of Project Settings.

#include "Ability/GA_MeleeAttack.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/Character.h"
#include "Controller/MyPlayerController.h"
#include "AttributeSet/MyAttributeSet.h"
#include "Character/MyEnemy.h"
#include "Kismet/GameplayStatics.h"

UGA_MeleeAttack::UGA_MeleeAttack()
{
	// 스킬 정보
	AbilityName = FText::FromString(TEXT("Melee Attack"));
	AbilityDescription = FText::FromString(TEXT("Basic melee attack"));
	AbilitySlot = 1; // 1번 키

	// 스킬 스펙
	CooldownDuration = 1.0f;
	StaminaCost = 10.0f;

	// 공격 스펙
	AttackRange = 200.0f; // 2m
	BaseDamage = 10.0f;
}

void UGA_MeleeAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	// 코스트 체크 및 적용
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	// 타겟 체크
	AActor* Target = GetCurrentTarget();
	if (!IsTargetValid(Target))
	{
		UE_LOG(LogTemp, Warning, TEXT("No valid target for Melee Attack"));
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	// 거리 체크
	float DistanceToTarget = GetDistanceToTarget(Target);
	if (DistanceToTarget > AttackRange)
	{
		UE_LOG(LogTemp, Warning, TEXT("Target too far: %.2f cm (max: %.2f cm)"), DistanceToTarget, AttackRange);
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	// 애니메이션 재생
	ACharacter* Character = GetAvatarCharacter();
	if (Character && AttackMontage)
	{
		Character->PlayAnimMontage(AttackMontage);
	}

	// 공격 실행
	PerformAttack();

	// Ability 종료
	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}

void UGA_MeleeAttack::PerformAttack()
{
	AActor* Target = GetCurrentTarget();
	if (!Target)
		return;

	// 데미지 적용
	ApplyDamageToTarget(Target);

	// 로그
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
		// ASC가 없으면 기본 UE 데미지 시스템 사용
		ACharacter* AvatarChar = GetAvatarCharacter();
		if (AvatarChar)
		{
			UGameplayStatics::ApplyDamage(Enemy, BaseDamage, AvatarChar->GetController(), AvatarChar, UDamageType::StaticClass());
		}
		return;
	}

	// ASC가 있으면 AttributeSet의 Health 직접 수정
	UMyAttributeSet* TargetAttributeSet = const_cast<UMyAttributeSet*>(TargetASC->GetSet<UMyAttributeSet>());
	if (TargetAttributeSet)
	{
		// 내 공격력 가져오기
		UMyAttributeSet* MyAttributeSet = GetMyAttributeSet();
		float FinalDamage = BaseDamage;

		if (MyAttributeSet)
		{
			FinalDamage += MyAttributeSet->GetAttackPower();
		}

		// 타겟의 방어력 적용
		FinalDamage -= TargetAttributeSet->GetDefense();
		FinalDamage = FMath::Max(FinalDamage, 1.0f); // 최소 1 데미지

		// 데미지 적용
		float NewHealth = TargetAttributeSet->GetHealth() - FinalDamage;
		TargetAttributeSet->SetHealth(NewHealth);

		UE_LOG(LogTemp, Log, TEXT("Dealt %.2f damage to %s (HP: %.2f)"), FinalDamage, *Enemy->GetName(), NewHealth);
	}
}
