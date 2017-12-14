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
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *HitLocation.ToString());
		GetControlledTank()->AimAt(HitLocation);
	}	
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	//Crosshait position in 2D Viewport
	int32 ViewportXSize, ViewportYSize;
	GetViewportSize(ViewportXSize, ViewportYSize);

	FVector2D ScreenLocation = FVector2D(ViewportXSize*CrosshairXLocation, ViewportYSize*CrosshairYLocation);
	FVector CameraWorldLocation, WorldDirection;
	
	if(DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, WorldDirection))
	{
		GetLookVectorHitLocation(CameraWorldLocation, WorldDirection, HitLocation);
		return true;
	}
	
	HitLocation = FVector(0);
	UE_LOG(LogTemp, Warning, TEXT("No screen deprojection"));
	return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector CameraWorldLocation, FVector WorldDirection, FVector& HitLocation) const
{
	FHitResult OutHit;
	//PlayerCameraManager->GetCameraLocation();
	if (GetWorld()->LineTraceSingleByChannel(
		OutHit,
		CameraWorldLocation,
		CameraWorldLocation + WorldDirection*HitDistance,
		ECollisionChannel::ECC_Visibility
		)) 
	{
		HitLocation = OutHit.Location;
		return true;
	}

	HitLocation = FVector(0);
	return false;
}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

