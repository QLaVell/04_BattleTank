// Copyright Quintin Oliver

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn* InPawn) {
	Super::SetPawn(InPawn);
	if (InPawn) {
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}
}

void ATankAIController::OnPossessedTankDeath() {
	UE_LOG(LogTemp, Warning, TEXT("Received"))
}

// Called every frame
void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();
	if (!ensure(PlayerTank && ControlledTank)) { return; }
	// Move towards player
	MoveToActor(PlayerTank, AcceptanceRadius); // TODO Check radius is in cm
	

	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	// Aim towards the player
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	// If locked, fire
	if (AimingComponent->GetFiringState() == EFiringState::Locked) {
		AimingComponent->Fire(); // TODO Limit fire rate
	}
}