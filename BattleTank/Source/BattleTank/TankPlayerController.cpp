// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Controlled tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Controlling %s"),*ControlledTank->GetName())
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	//UE_LOG(LogTemp, Warning, TEXT("Player Controller ticking"));
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *HitLocation.ToString());
	}	
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	//Crosshait position in 2D Viewport
	int32 ViewportXSize, ViewportYSize;
	GetViewportSize(ViewportXSize, ViewportYSize);

	FVector2D ScreenLocation = FVector2D(ViewportXSize*CrosshairXLocation, ViewportYSize*CrosshairYLocation);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *ScreenLocation.ToString())
	
	//	
	HitLocation = FVector(1.0);
	return false;
}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

