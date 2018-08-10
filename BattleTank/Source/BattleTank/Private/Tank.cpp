// Copyright Quintin Oliver

#include "BattleTank.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//DeathEffect = CreateDefaultSubobject<UParticleSystemComponent>(FName("Death Effect"));
	//DeathEffect->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	//DeathEffect->bAutoActivate = false;
}

void ATank::BeginPlay() {
	Super::BeginPlay();

	CurrentHealth = StartingHealth;
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) {
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp<int32>(DamagePoints, 0, CurrentHealth);

	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0) {
		OnDeath.Broadcast();
		if (FindComponentByClass<UParticleSystemComponent>()) {
			FindComponentByClass<UParticleSystemComponent>()->Activate();
		}
	}
	return DamageToApply;
}

float ATank::GetHealthPercent() const {
	return (float)CurrentHealth / (float)StartingHealth;
}