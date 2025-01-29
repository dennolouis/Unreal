#include "Combat/Weapon.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Combat/WeaponTraceComponent.h"

// Constructor
AWeapon::AWeapon()
{
    PrimaryActorTick.bCanEverTick = false;

    WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
    RootComponent = WeaponMesh;

    WeaponHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponHitbox"));
    WeaponHitbox->SetupAttachment(RootComponent);

    WeaponTraceComp = CreateDefaultSubobject<UWeaponTraceComponent>(TEXT("Trace Component"));
    WeaponTraceComp->SetWeaponHitBox(WeaponHitbox);
}

// BeginPlay
void AWeapon::BeginPlay()
{
    Super::BeginPlay();
}
