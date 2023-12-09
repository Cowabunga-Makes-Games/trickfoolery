// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_DetermineRandomPosition.h"

#pragma region UE Methods

UBTTask_DetermineRandomPosition::UBTTask_DetermineRandomPosition(FObjectInitializer const& ObjectInitializer) {
	NodeName = "Determine Random Position";
}

EBTNodeResult::Type UBTTask_DetermineRandomPosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	// Ensure the ACPP_EnemyAIController, Pawn, and NavigationSystem exist
	const ACPP_EnemyAIController* enemyController = Cast<ACPP_EnemyAIController>(OwnerComp.GetAIOwner());
	
	if (enemyController == nullptr) {
		return EBTNodeResult::Failed;
	}

	const APawn* enemyPawn = enemyController->GetPawn();
	const UNavigationSystemV1* navSystem = UNavigationSystemV1::GetCurrent(GetWorld());

	if (enemyPawn == nullptr || navSystem == nullptr) {
		return EBTNodeResult::Failed;
	}

	const auto playerPos = enemyPawn->GetActorLocation();

	FNavLocation targetPosition;
	if (navSystem->GetRandomPointInNavigableRadius(playerPos, SearchDistance, targetPosition)) {
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), targetPosition.Location);

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

#pragma endregion