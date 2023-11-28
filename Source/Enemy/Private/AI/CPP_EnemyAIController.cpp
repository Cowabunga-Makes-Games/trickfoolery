// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_EnemyAIController.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Sight.h"

ACPP_EnemyAIController::ACPP_EnemyAIController(FObjectInitializer const& ObjectInitializer) {
	SetupPerceptionSystem();
}

void ACPP_EnemyAIController::OnPossess(APawn* InPawn) {
	Super::OnPossess(InPawn);

	const ACPP_Enemy* Enemy = Cast<ACPP_Enemy>(InPawn);
	if (Enemy == nullptr) {
		return;
	}

	UBehaviorTree* BTBrain = Enemy->GetBehaviourTree();
	if (BTBrain == nullptr) {
		return;
	}

	UBlackboardComponent* blackboard;

	// Ensure a Blackboard Component will exist before referencing it
	UseBlackboard(BTBrain->BlackboardAsset, blackboard);
	Blackboard = blackboard;
			
	RunBehaviorTree(BTBrain);
}

void ACPP_EnemyAIController::SetupPerceptionSystem() {
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception Component")));
	
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("Hearing Config"));

	const auto PerceptionComp = GetPerceptionComponent();
	
	PerceptionComp->ConfigureSense(*SightConfig);
	PerceptionComp->ConfigureSense(*HearingConfig);
	
	// The sight sense will override the other senses
	PerceptionComp->SetDominantSense(*SightConfig->GetSenseImplementation());
	PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &ACPP_EnemyAIController::OnSenseUpdated);
}

void ACPP_EnemyAIController::OnSenseUpdated(AActor* Actor, FAIStimulus const Stimulus) {
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Target sighted or heard!");
}


