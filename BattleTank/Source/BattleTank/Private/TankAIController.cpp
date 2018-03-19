// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	ATank* ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("AIController does not have attached pawn."))
	} else {
		UE_LOG(LogTemp, Warning, TEXT("AIController controlling %s"), *ControlledTank->GetName())
	}
}

ATank * ATankAIController::GetControlledTank() {
	return Cast<ATank>(GetPawn());
}
