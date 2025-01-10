// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/Mainplayer.h"
#include "Interfaces/Fighter.h"
#include "MainCharacter.generated.h"

UCLASS()
class UNREAL_API AMainCharacter : public ACharacter, public IMainplayer, public IFighter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UAnimMontage* DeathAnimMontage;

	UPROPERTY(EditAnywhere)
	UAnimMontage* HurtAnimMontage;

public:
	// Sets default values for this character's properties
	AMainCharacter();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UStatsComponent* StatsComp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class ULockOnComponent* LockOnComp;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UCombatComponent* CombatComp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UTraceComponent* TraceComp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UBlockComponent* BlockComp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UPlayerActtionsComponent* PlayerActionsComp;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	class UPlayerAnimInstance* PlayerAnim;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float GetDamage() override;

	virtual bool HasEnoughStamina(float Cost) override;

	UFUNCTION(BlueprintCallable)
	void HandleDeath();

	virtual void EndLockOnWithActor(AActor* ActorRef) override;

	virtual bool CanTakeDamage(AActor* Opponent) override;

	UFUNCTION(BlueprintCallable)
	void PlayHurtAnim(TSubclassOf<class UCameraShakeBase> CameraShakeTemplate);

};
