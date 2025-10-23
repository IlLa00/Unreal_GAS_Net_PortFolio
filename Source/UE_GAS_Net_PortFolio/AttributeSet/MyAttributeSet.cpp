#include "MyAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UMyAttributeSet::UMyAttributeSet()
{
	InitHealth(100.0f);
	InitMaxHealth(100.0f);
	InitMana(100.0f);
	InitMaxMana(100.0f);
	InitStamina(100.0f);
	InitMaxStamina(100.0f);

	InitAttackPower(10.0f);
	InitDefense(5.0f);
	InitMagicPower(10.0f);
	InitMagicResistance(5.0f);

	InitMovementSpeed(1.0f);      
}

void UMyAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
		ClampAttribute(Attribute, NewValue, 0.0f, GetMaxHealth());
	else if (Attribute == GetManaAttribute())
		ClampAttribute(Attribute, NewValue, 0.0f, GetMaxMana());
	else if (Attribute == GetStaminaAttribute())
		ClampAttribute(Attribute, NewValue, 0.0f, GetMaxStamina());
	else if (Attribute == GetMaxHealthAttribute())
		ClampAttribute(Attribute, NewValue, 1.0f, 9999.0f);
	else if (Attribute == GetMaxManaAttribute())
		ClampAttribute(Attribute, NewValue, 0.0f, 9999.0f);
	else if (Attribute == GetMaxStaminaAttribute())
		ClampAttribute(Attribute, NewValue, 0.0f, 9999.0f);
	else if (Attribute == GetAttackPowerAttribute())
		ClampAttribute(Attribute, NewValue, 0.0f, 9999.0f);
	else if (Attribute == GetDefenseAttribute())
		ClampAttribute(Attribute, NewValue, 0.0f, 9999.0f);
	else if (Attribute == GetMagicPowerAttribute())
		ClampAttribute(Attribute, NewValue, 0.0f, 9999.0f);
	else if (Attribute == GetMagicResistanceAttribute())
		ClampAttribute(Attribute, NewValue, 0.0f, 9999.0f);
	else if (Attribute == GetMovementSpeedAttribute())
		ClampAttribute(Attribute, NewValue, 0.1f, 3.0f);
}

void UMyAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FGameplayEffectContextHandle Context = Data.EffectSpec.GetContext();
	UAbilitySystemComponent* SourceASC = Context.GetOriginalInstigatorAbilitySystemComponent();
	const FGameplayTagContainer& SourceTags = *Data.EffectSpec.CapturedSourceTags.GetAggregatedTags();

	AActor* TargetActor = nullptr;
	AController* TargetController = nullptr;

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
	}

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));

		if (GetHealth() <= 0.0f)
			UE_LOG(LogTemp, Warning, TEXT("%s has died!"), *GetNameSafe(TargetActor));
	}
	else if (Data.EvaluatedData.Attribute == GetManaAttribute())
		SetMana(FMath::Clamp(GetMana(), 0.0f, GetMaxMana()));
	else if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
		SetStamina(FMath::Clamp(GetStamina(), 0.0f, GetMaxStamina()));
	else if (Data.EvaluatedData.Attribute == GetMaxHealthAttribute())
	{
		if (GetHealth() > GetMaxHealth())
			SetHealth(GetMaxHealth());
	}
	else if (Data.EvaluatedData.Attribute == GetMovementSpeedAttribute())
	{
		if (ACharacter* Character = Cast<ACharacter>(TargetActor))
		{
			if (UCharacterMovementComponent* MovementComp = Character->GetCharacterMovement())
			{
				const float BaseSpeed = 600.0f; // Default UE5 walk speed
				MovementComp->MaxWalkSpeed = BaseSpeed * GetMovementSpeed();
			}
		}
	}
}

void UMyAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet, MaxStamina, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet, AttackPower, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet, Defense, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet, MagicPower, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet, MagicResistance, COND_None, REPNOTIFY_Always);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet, MovementSpeed, COND_None, REPNOTIFY_Always);
}

void UMyAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, Health, OldHealth);
}

void UMyAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, MaxHealth, OldMaxHealth);
}

void UMyAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, Mana, OldMana);
}

void UMyAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, MaxMana, OldMaxMana);
}

void UMyAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, Stamina, OldStamina);
}

void UMyAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, MaxStamina, OldMaxStamina);
}

void UMyAttributeSet::OnRep_AttackPower(const FGameplayAttributeData& OldAttackPower)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, AttackPower, OldAttackPower);
}

void UMyAttributeSet::OnRep_Defense(const FGameplayAttributeData& OldDefense)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, Defense, OldDefense);
}

void UMyAttributeSet::OnRep_MagicPower(const FGameplayAttributeData& OldMagicPower)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, MagicPower, OldMagicPower);
}

void UMyAttributeSet::OnRep_MagicResistance(const FGameplayAttributeData& OldMagicResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, MagicResistance, OldMagicResistance);
}

void UMyAttributeSet::OnRep_MovementSpeed(const FGameplayAttributeData& OldMovementSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, MovementSpeed, OldMovementSpeed);
}

void UMyAttributeSet::ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue, float MinValue, float MaxValue)
{
	NewValue = FMath::Clamp(NewValue, MinValue, MaxValue);
}
