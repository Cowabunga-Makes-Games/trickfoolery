// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_DetermineRandomPosition.generated.h"

/**
 * 
 */
UCLASS()
class UBTTask_DetermineRandomPosition : public UBTTask_BlackboardBase {
	GENERATED_BODY()
	
public:
	explicit UBTTask_DetermineRandomPosition(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy AI", meta=(AllowPrivateAccess="true"))
	float SearchDistance = 1500.f;
};
