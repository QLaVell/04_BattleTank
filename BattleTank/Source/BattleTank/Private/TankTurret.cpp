// Copyright Quintin Oliver

#include "BattleTank.h"
#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed) {
	// Clamp the Relative Speed
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	// Calculate Rotation
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto Rotation = RelativeRotation.Yaw + RotationChange;
	SetRelativeRotation(FRotator(0, Rotation, 0));
}
