#include "Combat/WeaponTraceComponent.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/DamageType.h" // Include for damage handling
#include "Engine/DamageEvents.h"

// Constructor
UWeaponTraceComponent::UWeaponTraceComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

// BeginPlay: Find the weapon hitbox
void UWeaponTraceComponent::BeginPlay()
{
    Super::BeginPlay();

    AActor* OwnerActor = GetOwner();
    if (OwnerActor)
    {
        WeaponHitbox = OwnerActor->FindComponentByClass<UBoxComponent>();
    }
}

// StartAttack: Detect hits using the hitbox
void UWeaponTraceComponent::StartAttack()
{
    if (!WeaponHitbox) return;

    FVector BoxExtent = WeaponHitbox->GetScaledBoxExtent();
    FVector Start = WeaponHitbox->GetComponentLocation();
    FVector End = Start;

    TArray<FHitResult> OutHits;
    FCollisionShape Box = FCollisionShape::MakeBox(BoxExtent);
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActors(TargetsToIgnore);
    QueryParams.AddIgnoredActor(GetOwner());

    bool bHit = GetWorld()->SweepMultiByChannel(
        OutHits, Start, End, FQuat::Identity, ECC_Pawn, Box, QueryParams
    );

    if (bDebugMode)
    {
        FColor DebugColor = bHit ? FColor::Green : FColor::Red;
        DrawDebugBox(GetWorld(), Start, BoxExtent, DebugColor, false, 1.0f, 0, 2.0f);
    }

    for (const FHitResult& Hit : OutHits)
    {
        AActor* HitActor = Hit.GetActor();
        if (!HitActor || TargetsToIgnore.Contains(HitActor)) continue;

        FDamageEvent DamageEvent; // Proper instantiation
        HitActor->TakeDamage(10.0f, DamageEvent, GetOwner()->GetInstigatorController(), GetOwner());
        TargetsToIgnore.AddUnique(HitActor);

        if (HitParticleTemplate)
        {
            UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticleTemplate, Hit.ImpactPoint);
        }
    }
}

// StopAttack: Reset hit tracking
void UWeaponTraceComponent::StopAttack()
{
    TargetsToIgnore.Empty();
}

void UWeaponTraceComponent::SetWeaponHitBox(UBoxComponent* HitBox)
{
    WeaponHitbox = HitBox;
}
