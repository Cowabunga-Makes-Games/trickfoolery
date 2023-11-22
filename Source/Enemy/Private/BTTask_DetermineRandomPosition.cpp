// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_DetermineRandomPosition.h"

UBTTask_DetermineRandomPosition::UBTTask_DetermineRandomPosition(FObjectInitializer const& ObjectInitializer) {
	NodeName = "Determine Random Position";
}

EBTNodeResult::Type UBTTask_DetermineRandomPosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	// Ensure the ACPP_EnemyAIController, Pawn, and NavigationSystem exist
	const ACPP_EnemyAIController* EnemyController = Cast<ACPP_EnemyAIController>(OwnerComp.GetAIOwner());
	
	if (EnemyController == nullptr) {
		return EBTNodeResult::Failed;
	}

	const APawn* EnemyPawn = EnemyController->GetPawn();
	const UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());

	if (EnemyPawn == nullptr || NavSystem == nullptr) {
		return EBTNodeResult::Failed;
	}

	const auto playerPos = EnemyPawn->GetActorLocation();

	FNavLocation targetPosition;
	if (NavSystem->GetRandomPointInNavigableRadius(playerPos, SearchDistance, targetPosition)) {
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), targetPosition.Location);

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}