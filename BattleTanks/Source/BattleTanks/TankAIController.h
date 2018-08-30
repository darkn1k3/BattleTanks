// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

// Forward Declarations
class ATank;

UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
private:
	void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	// Getting AI Controlled Tank for logging the possessed tanks by AI (for now)
	ATank * GetAIControlledTank() const;

	// AI tries to find the player tank (our tank)
	ATank * GetPlayerTank() const;
};