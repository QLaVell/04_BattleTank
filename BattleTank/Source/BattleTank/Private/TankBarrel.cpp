// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"

void UTankBarrel::Elevate(float DegreesPerSecond) {
	// Move the barrel to right amount this frame
	// Given a max elevation speed and the frame time
	UE_LOG(LogTemp, Warning, TEXT("Barrel->Elevate() call with speed %f"), DegreesPerSecond);
}