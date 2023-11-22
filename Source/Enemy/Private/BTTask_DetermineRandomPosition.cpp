// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_DetermineRandomPosition.h"

#include "CPP_EnemyAIController.h"

UBTTask_DetermineRandomPosition::UBTTask_DetermineRandomPosition(FObjectInitializer const& ObjectInitializer) {
	NodeName = "Determine Random Position";
}

EBTNodeResult::Type UBTTask_DetermineRandomPosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	// Ensure the AIController is ACPP_EnemyAIController and the controlled Pawn and NavigationSystem exist
	if (auto* const controller = Cast<ACPP_EnemyAIController>(OwnerComp.GetAIOwner())) {
		if (auto* const enemy = controller->GetPawn()) {
			if (auto* const navSystem = UNavigationSystemV1::GetCurrent(GetWorld())) {
				auto const playerPos = enemy->GetActorLocation();

				FNavLocation targetPosition;
				if (navSystem->GetRandomPointInNavigableRadius(playerPos, SearchDistance, targetPosition)) {
					OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), targetPosition.Location);
				}

				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	
	return EBTNodeResult::Failed;
}