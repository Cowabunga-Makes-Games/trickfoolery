// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_EnemyAIController.h"

#pragma region UE Methods

ACPP_EnemyAIController::ACPP_EnemyAIController(FObjectInitializer const& ObjectInitializer) {
	SetupPerceptionSystem();
}

void ACPP_EnemyAIController::OnPossess(APawn* InPawn) {
	Super::OnPossess(InPawn);

	const ACPP_Enemy* enemy = Cast<ACPP_Enemy>(InPawn);
	if (enemy == nullptr) {
		return;
	}

	UBehaviorTree* BTBrain = enemy->GetBehaviourTree();
	if (BTBrain == nullptr) {
		return;
	}

	UBlackboardComponent* blackboard;

	// Ensure a Blackboard Component will exist before referencing it
	UseBlackboard(BTBrain->BlackboardAsset, blackboard);
	Blackboard = blackboard;
			
	RunBehaviorTree(BTBrain);
}

#pragma endregion

#pragma region AI Perception System

void ACPP_EnemyAIController::SetupPerceptionSystem() {
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception Component")));
	
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("Hearing Config"));
	DamageConfig = CreateDefaultSubobject<UAISenseConfig_Damage>(TEXT("Damage Config"));
	
	const auto perceptionComp = GetPerceptionComponent();
	
	perceptionComp->ConfigureSense(*SightConfig);
	perceptionComp->ConfigureSense(*HearingConfig);
	perceptionComp->ConfigureSense(*DamageConfig);
	
	// The sight sense will override the other senses
	perceptionComp->SetDominantSense(*SightConfig->GetSenseImplementation());
	perceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &ACPP_EnemyAIController::OnSenseUpdated);

	// Cache to cut extra runtime by repeated access of such values when the AI Perception system updates
	SightID = SightConfig->GetSenseID();
	HearingID = HearingConfig->GetSenseID();
	DamageID = DamageConfig->GetSenseID();
}

void ACPP_EnemyAIController::OnSenseUpdated(AActor* Actor, FAIStimulus Stimulus) {
	if (Stimulus.Type == SightID) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Target sighted!");
	} else if (Stimulus.Type == HearingID) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Target heard!");
	}
	
}

#pragma endregion

