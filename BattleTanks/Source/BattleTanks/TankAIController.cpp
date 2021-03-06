// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "GameFramework/Pawn.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn); // Call the super's SetPawn because we don't want to temper with what it does
	if (InPawn)
	{
		ATank* PossessedTank = Cast<ATank>(InPawn);
		if (!PossessedTank) { return; } // if Mortar, don't trigger OnTankDeath event

		PossessedTank->OnTankDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto AIControlledTank = GetPawn();
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	
	if (!ensure(PlayerTank && AIControlledTank)) { return; }

	MoveToActor(PlayerTank, AcceptanceRadius);

	auto AimingComponent = AIControlledTank->FindComponentByClass<UTankAimingComponent>();
	AimingComponent->AimAt(PlayerTank->GetTargetLocation());
	
	// AI tank should fire only when locked on target
	if (AimingComponent->GetFiringState() == EFiringStatus::Locked)
	{
		AimingComponent->Fire(); // TODO: limit firing rate
	}
}

void ATankAIController::OnTankDeath()
{
	if (!GetPawn()) { return; }
	GetPawn()->DetachFromControllerPendingDestroy();
}
