// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/Character.h"
#include "CPP_Enemy.generated.h"

UCLASS()
class ENEMY_API ACPP_Enemy : public ACharacter {
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACPP_Enemy();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UBehaviorTree* GetBehaviourTree() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI", meta=(AllowPrivateAccess="true"))
		UBehaviorTree* AIBrain;
};
