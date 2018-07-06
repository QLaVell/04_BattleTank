// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
<<<<<<< HEAD
=======
#include "public/Tank.h"
>>>>>>> ff12ec66c9dce386453d1dc3b8154e7d8ff3a358
#include "TankAIController.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
}

// Called every frame
void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
<<<<<<< HEAD
	auto ControlledTank = GetPawn();
	if (!ensure(PlayerController && ControlledTank)) { return; }
	// Move towards player
	MoveToActor(PlayerTank, AcceptanceRadius); // TODO Check radius is in cm

	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	// Aim towards the player
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	// TODO Fix firing
	//ControlledTank->Fire();	
=======
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	if (ensure(PlayerTank)) {
		// Move towards player
		MoveToActor(PlayerTank, AcceptanceRadius); // TODO Check radius is in cm

		// Aim towards the player
		AimingComponent->AimAt(PlayerTank->GetActorLocation());

		//ControlledTank->Fire();
	}
	
>>>>>>> ff12ec66c9dce386453d1dc3b8154e7d8ff3a358
}