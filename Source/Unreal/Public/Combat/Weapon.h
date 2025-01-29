#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Weapon.generated.h"

UCLASS()
class UNREAL_API AWeapon : public AActor
{
    GENERATED_BODY()

public:
    AWeapon();

protected:
    virtual void BeginPlay() override;

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
    UStaticMeshComponent* WeaponMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
    UBoxComponent* WeaponHitbox;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    class UWeaponTraceComponent* WeaponTraceComp;
};
