#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponTraceComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNREAL_API UWeaponTraceComponent : public UActorComponent
{
    GENERATED_BODY()

private:
    UPROPERTY(EditAnywhere, Category = "Weapon Trace")
    TArray<AActor*> TargetsToIgnore;

    UPROPERTY(EditAnywhere, Category = "Weapon Trace")
    bool bDebugMode = false;

    UPROPERTY(EditAnywhere, Category = "Weapon Trace")
    UParticleSystem* HitParticleTemplate;

    UPROPERTY()
    class UBoxComponent* WeaponHitbox; // Ensure this is declared

public:
    UWeaponTraceComponent();

protected:
    virtual void BeginPlay() override;

public:
    UFUNCTION(BlueprintCallable)
    void StartAttack();

    UFUNCTION(BlueprintCallable)
    void StopAttack();

    void SetWeaponHitBox(UBoxComponent* HitBox);
};
