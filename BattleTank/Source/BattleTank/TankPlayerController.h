// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

//Forward Declaration
class ATank;
/**
 * 
 */

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATank* GetControlledTank() const;

	virtual void BeginPlay() override;	
	virtual void Tick(float) override;

private:

	// Start the tank moving the barrel so a shot whould it there
	// the crosshair intersects the world
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector&) const;
	bool GetLookVectorHitLocation(FVector, FVector, FVector&) const;

	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5;

	UPROPERTY(EditAnywhere)
	float CrosshairYLocation = 0.3333;

	UPROPERTY(EditAnywhere)
	float HitDistance = 1000000;
};
