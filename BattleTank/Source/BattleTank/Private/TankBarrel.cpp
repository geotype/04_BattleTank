// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"
#include "Runtime/Engine/Classes/Engine/World.h"

void UTankBarrel::ElevateBarrel(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	auto ElevationChange = RelativeSpeed * MaxDegreePerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;

	auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);
	SetRelativeRotation(FRotator(Elevation, 0, 0));
	//UE_LOG(LogTemp, Warning, TEXT("Barrel-Elevate at speed %f"), RelativeSpeed);
}


