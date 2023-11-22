// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_EnemyAIController.h"

ACPP_EnemyAIController::ACPP_EnemyAIController(FObjectInitializer const& ObjectInitializer) {
	
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
