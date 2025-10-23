#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AbilitySystemInterface.h"
#include "MyPlayerController.generated.h"

class UInputAction;

UCLASS()
class UE_GAS_NET_PORTFOLIO_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMyPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CurrentTarget, Category = "Targeting")
	class AMyEnemy* CurrentTarget;

	UFUNCTION()
	void OnRep_CurrentTarget();

	UFUNCTION(BlueprintCallable, Category = "Targeting")
	void ToggleTargetSelection();

	UFUNCTION(BlueprintCallable, Category = "Targeting")
	void ClearTarget();

	UFUNCTION(Server, Reliable, Category = "Targeting")
	void Server_SetTarget(AMyEnemy* NewTarget);

protected:
	AMyEnemy* FindNearestEnemy();

	UPROPERTY(EditDefaultsOnly, Category = "Targeting")
	float MaxTargetDistance = 3000.0f; 

	UPROPERTY(EditDefaultsOnly, Category = "Targeting")
	float TargetingFOV = 180.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Targeting")
	FName TargetableTag = TEXT("Enemy");

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* JumpAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* SprintAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* TargetToggleAction;

	void OnMove(const struct FInputActionValue& Value);
	void OnLook(const struct FInputActionValue& Value);
	void OnJumpStarted();
	void OnJumpCompleted();
	void OnSprintStarted();
	void OnSprintCompleted();
	void OnTargetToggle();

	// ================================================================
	// Ability Activation
	// ================================================================
protected:
	/** Ability 슬롯별 Input Actions (1~6번 키) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Abilities")
	UInputAction* Ability1Action;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Abilities")
	UInputAction* Ability2Action;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Abilities")
	UInputAction* Ability3Action;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Abilities")
	UInputAction* Ability4Action;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Abilities")
	UInputAction* Ability5Action;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Abilities")
	UInputAction* Ability6Action;

	/** Ability 활성화 콜백 */
	void OnAbility1();
	void OnAbility2();
	void OnAbility3();
	void OnAbility4();
	void OnAbility5();
	void OnAbility6();

public:
	/** 슬롯 번호로 Ability 활성화 */
	UFUNCTION(BlueprintCallable, Category = "GAS")
	void ActivateAbilityBySlot(int32 SlotNumber);

	/** AbilitySystemComponent 가져오기 */
	UFUNCTION(BlueprintCallable, Category = "GAS")
	class UAbilitySystemComponent* GetASC();
};
