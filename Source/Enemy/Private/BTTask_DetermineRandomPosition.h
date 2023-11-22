// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NavigationSystem.h"
#include "CPP_EnemyAIController.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BTTask_DetermineRandomPosition.generated.h"

//*******************************************************************************************
// BTTask_DetermineRandomPosition
//*******************************************************************************************
/**
 * Determine Random Position task node.
 * Finds a random location using the navigation system.
 */
UCLASS()
class UBTTask_DetermineRandomPosition : public UBTTask_BlackboardBase {
	GENERATED_BODY()
	
public:
	explicit UBTTask_DetermineRandomPosition(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	/**
	 * The radius from the Pawn position to determine the extent of the navigable space through the navigation system.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy AI", meta=(AllowPrivateAccess="true"))
		float SearchDistance = 1000.f;
};
