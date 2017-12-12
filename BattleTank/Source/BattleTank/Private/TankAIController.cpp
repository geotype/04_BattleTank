// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto AIControlledTank = Cast<ATank>(GetPawn());
	if (!AIControlledTank)	{	UE_LOG(LogTemp, Warning, TEXT("no Tank is controlled by AI"))	}
		else	{	UE_LOG(LogTemp, Warning, TEXT("%s is controlled by AI"), *AIControlledTank->GetName())	}

	auto PlayerControlledTank = GetPlayerControlledTank();
	if (!PlayerControlledTank) {	UE_LOG(LogTemp, Warning, TEXT("no Tank is controlled by Player"))	}
		else {	UE_LOG(LogTemp, Warning, TEXT("%s is controlled by Player"), *PlayerControlledTank->GetName()) 	}


}

ATank* ATankAIController::GetPlayerControlledTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) { return nullptr; }

	return Cast<ATank>(PlayerPawn);
}
