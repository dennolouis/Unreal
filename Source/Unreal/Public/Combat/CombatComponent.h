// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(
	FOnAttackPerformedSignature,
	UCombatComponent, OnAttackPerformedDelegate,
	float, Amount
);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREAL_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<UAnimMontage*> LightAttackAnimations;

	UPROPERTY(EditAnywhere)
	TArray<UAnimMontage*> HeavyAttackAnimations;

	ACharacter* CharacterRef;

	UPROPERTY(VisibleAnywhere)
	int LightComboCounter{ 0 };

	UPROPERTY(VisibleAnywhere)
	int HeavyComboCounter{ 0 };

	UPROPERTY(VisibleAnywhere)
	bool bCanAttack{ true };

	UPROPERTY(EditAnywhere)
	float StaminaCost{5.0f};

	UPROPERTY(EditAnywhere)
	float HeavyStaminaCost{ 5.0f };

public:	
	// Sets default values for this component's properties
	UCombatComponent();

	UPROPERTY(BlueprintAssignable)
	FOnAttackPerformedSignature OnAttackPerformedDelegate;

	float AnimDuration;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void ComboAttack(bool isLightAttack = true);

	UFUNCTION(BlueprintCallable)
	void HandleResetAttack();

	UFUNCTION(BlueprintCallable)
	void ResetComboCounter();

	UFUNCTION(BlueprintPure)
	bool IsAttacking() const;

	void StopAttackAnimation();

	UFUNCTION()
	void RandomAttack();		
};
