// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_EnemyAIController.h"

#include "CPP_Enemy.h"

ACPP_EnemyAIController::ACPP_EnemyAIController(FObjectInitializer const& ObjectInitializer) {
	
}

void ACPP_EnemyAIController::OnPossess(APawn* InPawn) {
	Super::OnPossess(InPawn);

	if (auto* const enemy = Cast<ACPP_Enemy>(InPawn)) {
		if (auto* const BTBrain = enemy->GetBehaviourTree()) {
			UBlackboardComponent* blackboard;

			// Ensure a Blackboard Component will exist before referencing it
			UseBlackboard(BTBrain->BlackboardAsset, blackboard);
			Blackboard = blackboard;
			
			RunBehaviorTree(BTBrain);
		}
	}
}
