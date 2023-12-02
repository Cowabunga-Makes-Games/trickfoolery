// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CPP_Enemy.h"
#include "Perception/AIPerceptionTypes.h"
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

private:
	class UAISenseConfig_Sight* SightConfig;
	class UAISenseConfig_Hearing* HearingConfig;
	class UAISenseConfig_Damage* DamageConfig;
	
	FAISenseID SightID;
	FAISenseID HearingID;
	FAISenseID DamageID;

	void SetupPerceptionSystem();

	UFUNCTION()
		void OnSenseUpdated(AActor* Actor, FAIStimulus Stimulus); 
};
