// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_DetermineRandomPosition.h"

UBTTask_DetermineRandomPosition::UBTTask_DetermineRandomPosition(FObjectInitializer const& ObjectInitializer) {
	NodeName = "Determine Random Position";
}

EBTNodeResult::Type UBTTask_DetermineRandomPosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}