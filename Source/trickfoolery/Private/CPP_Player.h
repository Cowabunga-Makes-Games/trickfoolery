// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "CPP_InputConfigData.h"
#include "CPP_Player.generated.h"

//*******************************************************************************************
// ACPP_Player
//*******************************************************************************************
/// <summary>
/// Extends the ACharacter class to implement core player movement, dash, and taunt
/// mechanics.
/// </summary>
UCLASS()
class TRICKFOOLERY_API ACPP_Player : public ACharacter {
	GENERATED_BODY()

#pragma region UE Methods
	
public:
	// Sets default values for this character's properties
	ACPP_Player();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

#pragma endregion

#pragma region Input

protected:
	// Get a pointer to the UInputMappingContext in the editor
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputMappingContext* InputMapping;
	
	// Get a pointer to the defined InputActions to bind the Actions to functions
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UCPP_InputConfigData* InputActions;

	// The speed multiplier for the movement in the level
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	float MovementSpeed;

private:
	void Move(const FInputActionValue& Value);

#pragma endregion 

};
