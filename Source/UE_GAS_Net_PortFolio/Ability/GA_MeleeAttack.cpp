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
	AbilityDescription = FText::FromString(TEXT("Basic melee attack with combo system"));
	AbilitySlot = 1; // 1번 키

	CooldownDuration = 0.5f; // 콤보를 위해 쿨다운 감소
	StaminaCost = 10.0f;

	AttackRange = 300.0f;
	BaseDamage = 10.0f;

	// 콤보 설정
	MaxComboCount = 3;
	ComboResetTime = 1.5f;
	CurrentComboCount = 0;
}

void UGA_MeleeAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	// 콤보 카운트 증가
	CurrentComboCount++;
	if (CurrentComboCount > MaxComboCount)
	{
		CurrentComboCount = 1; // 최대 콤보 도달 시 1번으로 리셋
	}

	UE_LOG(LogTemp, Log, TEXT("Combo Attack: %d"), CurrentComboCount);

	// 콤보 애니메이션 재생
	PlayComboMontage();

	// 콤보 리셋 타이머 갱신
	ACharacter* Character = GetAvatarCharacter();
	if (Character)
	{
		Character->GetWorldTimerManager().ClearTimer(ComboResetTimerHandle);
		Character->GetWorldTimerManager().SetTimer(
			ComboResetTimerHandle,
			this,
			&UGA_MeleeAttack::ResetCombo,
			ComboResetTime,
			false
		);
	}

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

void UGA_MeleeAttack::ResetCombo()
{
	CurrentComboCount = 0;
	UE_LOG(LogTemp, Log, TEXT("Combo Reset"));
}

void UGA_MeleeAttack::PlayComboMontage()
{
	ACharacter* Character = GetAvatarCharacter();
	if (!Character) return;

	// ComboMontages 배열에 몽타주가 설정되어 있으면 사용
	if (ComboMontages.IsValidIndex(CurrentComboCount - 1) && ComboMontages[CurrentComboCount - 1])
	{
		UAnimMontage* MontageToPlay = ComboMontages[CurrentComboCount - 1];
		Character->PlayAnimMontage(MontageToPlay);
		UE_LOG(LogTemp, Log, TEXT("Playing Combo Montage %d: %s"), CurrentComboCount, *MontageToPlay->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Combo Montage %d not set! Please add montages to ComboMontages array in Blueprint."), CurrentComboCount);
	}
}
