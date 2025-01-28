// Fill out your copyright notice in the Description page of Project Settings.


#include "Combat/CombatComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "Interfaces/Mainplayer.h"

// Sets default values for this component's properties
UCombatComponent::UCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	CharacterRef = GetOwner<ACharacter>();
	
}


// Called every frame
void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCombatComponent::ComboAttack(bool isLightAttack)
{
    if (CharacterRef->Implements<UMainplayer>())
    {
        IMainplayer* IPlayerRef{ Cast<IMainplayer>(CharacterRef) };

        if (IPlayerRef && !IPlayerRef->HasEnoughStamina(isLightAttack ? StaminaCost : HeavyStaminaCost))
        {
            return;
        }
    }

    if (!bCanAttack) { return; }

    bCanAttack = false;

    float AttackAnimDuration = CharacterRef->PlayAnimMontage(
        isLightAttack ? LightAttackAnimations[LightComboCounter] : HeavyAttackAnimations[HeavyComboCounter]
    );

    // Increment and wrap the combo counter
    if (isLightAttack)
    {
        LightComboCounter = (LightComboCounter + 1) % LightAttackAnimations.Num();
    }
    else
    {
        HeavyComboCounter = (HeavyComboCounter + 1) % HeavyAttackAnimations.Num();
    }

    OnAttackPerformedDelegate.Broadcast(StaminaCost);
}


void UCombatComponent::HandleResetAttack()
{
	bCanAttack = true;
}

void UCombatComponent::RandomAttack()
{
	int RandomIndex{
		FMath::RandRange(0, LightAttackAnimations.Num() - 1)
	};

	AnimDuration = CharacterRef->PlayAnimMontage(LightAttackAnimations[RandomIndex]);
}

void UCombatComponent::ResetComboCounter()
{
	LightComboCounter = 0;
	HeavyComboCounter = 0;
}

bool UCombatComponent::IsAttacking() const
{
	return !bCanAttack;
}

void UCombatComponent::StopAttackAnimation()
{
	if (CharacterRef) 
	{ 
		CharacterRef->StopAnimMontage(); 
		bCanAttack = true; 
	}
}

