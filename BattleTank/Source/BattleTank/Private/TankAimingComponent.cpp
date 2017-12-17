// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { 

		FString TankName = GetOwner()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("%s has no Barrel"), *TankName);
		return; }

	FVector OutLaunchVelocity = FVector(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace //comment this to generate the bug
	);

	if (bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		FString TankName = GetOwner()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"), *TankName, *AimDirection.ToString());
		//MoveBarrel(AimDirection);
	}
	else
	{
		FString TankName = GetOwner()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("%s is not aiming"), *TankName);
	}

}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	UE_LOG(LogTemp, Warning, TEXT("AimAsRotator %s"), *DeltaRotator.ToString());

	Barrel->ElevateBarrel(5);
}



void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	Barrel = BarrelToSet;
}


