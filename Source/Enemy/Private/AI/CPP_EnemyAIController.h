// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CPP_Enemy.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Damage.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Sight.h"
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

#pragma region UE Methods
	
public:
	explicit ACPP_EnemyAIController(FObjectInitializer const& ObjectInitializer);

protected:
	virtual void OnPossess(APawn* InPawn) override;

#pragma endregion

#pragma region AI Perception System

private:
	/** Manages the configuration and updates to the AI perception sight sense. */
	class UAISenseConfig_Sight* SightConfig;
	/** Manages the configuration and updates to the AI perception hearing sense. */
	class UAISenseConfig_Hearing* HearingConfig;
	/** Manages the configuration and updates to the AI perception damage sense. */
	class UAISenseConfig_Damage* DamageConfig;

	/** Provides identification for the sight sense to distinguish stimulus types when sensed. */
	FAISenseID SightID;
	/** Provides identification for the hearing sense to distinguish stimulus types when sensed. */
	FAISenseID HearingID;
	/** Provides identification for the damage sense to distinguish stimulus types when sensed. */
	FAISenseID DamageID;

	/** Initializes the AI Perception system and configures its senses for operation. */
	void SetupPerceptionSystem();

	/** Triggers when the perception system has detected a stimulus for any of its senses. */
	UFUNCTION()
		void OnSenseUpdated(AActor* Actor, FAIStimulus Stimulus);

#pragma endregion
	
};
