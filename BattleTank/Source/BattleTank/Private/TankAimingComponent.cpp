// Copyright Quintin Oliver

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"

void UTankAimingComponent::BeginPlay() {
	Super::BeginPlay();
	LastFireTime = GetWorld()->GetTimeSeconds();
}

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {
	if (GetRoundsLeft() <= 0) {
		FiringState = EFiringState::OutOfAmmo;
	} else if ((GetWorld()->GetTimeSeconds() - LastFireTime < ReloadTimeInSeconds)) {
		FiringState = EFiringState::Reloading;
	} else if (IsBarrelMoving()) {
		FiringState = EFiringState::Aiming;
	} else {
		FiringState = EFiringState::Locked;
	}
}

EFiringState UTankAimingComponent::GetFiringState() const {
	return FiringState;
}

bool UTankAimingComponent::IsBarrelMoving() {
	if (!ensure(Barrel)) { return false; }
	auto BarrelForward = Barrel->GetForwardVector();
	return !BarrelForward.Equals(AimDirection, 0.01);
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet) {
	if (!ensure(BarrelToSet && TurretToSet)) { return; }
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation) {
	if (!ensure(Barrel)) { return; }
	
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0
		,ESuggestProjVelocityTraceOption::DoNotTrace
	);
	// Calculate the OutLaunchVelocity
	if (bHaveAimSolution) {
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		auto TankName = GetOwner()->GetName();
		
		MoveBarrelTowards();
	}
}

void UTankAimingComponent::Fire() {
	if (FiringState == EFiringState::Locked || FiringState == EFiringState::Aiming) {
		// Spawn a projectile at the socket location of the barrel
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("RoundsBefore: %d, RoundsAfter: %d"), RoundsLeft--, RoundsLeft)
		RoundsLeft--;
	}
}

int32 UTankAimingComponent::GetRoundsLeft() const {
	return RoundsLeft;
}

void UTankAimingComponent::MoveBarrelTowards() {
	if (!ensure(Barrel && Turret)) { return; }

	// Calculate difference between current barrel rotation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	Barrel->Elevate(DeltaRotator.Pitch);
	if (FMath::Abs(DeltaRotator.Yaw) < 180) {
		Turret->Rotate(DeltaRotator.Yaw);
	} else {
		Turret->Rotate(-DeltaRotator.Yaw);
	}
}