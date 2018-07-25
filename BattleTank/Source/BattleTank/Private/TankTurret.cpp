// Copyright Quintin Oliver

#include "BattleTank.h"
#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed) {
	// Clamp the Relative Speed
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	// Calculate Rotation
	float RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float Rotation = RelativeRotation.Yaw + RotationChange;
	SetRelativeRotation(FRotator(0, Rotation, 0));
}
