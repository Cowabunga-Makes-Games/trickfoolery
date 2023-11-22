// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CPP_Enemy.h"
#include "CPP_EnemyAIController.generated.h"

//*******************************************************************************************
// CPP_EnemyAIController
//*******************************************************************************************
/**
 * Initializes and runs the BehaviorTree associated with the active possessed Pawn.
 */
UCLASS()
class ACPP_EnemyAIController : public AAIController {
	GENERATED_BODY()

public:
	explicit ACPP_EnemyAIController(FObjectInitializer const& ObjectInitializer);

protected:
	virtual void OnPossess(APawn* InPawn) override;
};
