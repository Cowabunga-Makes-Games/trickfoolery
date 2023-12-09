// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/Character.h"
#include "CPP_Enemy.generated.h"

//*******************************************************************************************
// CPP_Enemy
//*******************************************************************************************
/**
 * Extends the ACharacter class to set the AIController and BehaviorTree for an Enemy type
 * to execute the associated AI.
 */
UCLASS()
class ENEMY_API ACPP_Enemy : public ACharacter {
	GENERATED_BODY()

#pragma region UE Methods
	
public:
	// Sets default values for this character's properties
	ACPP_Enemy();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

#pragma endregion

#pragma region AI

public:
	/** Retrieves the behaviour tree associated with this Character. */
	UBehaviorTree* GetBehaviourTree() const;

protected:
	/** Operates the enemy behaviour logic. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
		UBehaviorTree* AIBrain;

#pragma endregion
	
};
