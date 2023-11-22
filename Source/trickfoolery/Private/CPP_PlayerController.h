// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "CPP_Player.h"
#include "CPP_PlayerController.generated.h"

//*******************************************************************************************
// CPP_PlayerController
//*******************************************************************************************
/** Links the Enhanced Input System bindings to the active possessed Pawn. */
UCLASS()
class ACPP_PlayerController : public APlayerController {
	GENERATED_BODY()

#pragma region UE Methods
	
public:
	ACPP_PlayerController();

protected:
	virtual void SetupInputComponent() override;
	
	// To add mapping context
	virtual void BeginPlay();

#pragma endregion

#pragma region Input

protected:
	/** Reference to the UInputMappingContext to be used to receive player input. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
		UInputMappingContext* InputMappingContext;
	
	/** Reference to the defined InputActions to bind input events to this character's methods. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
		UCPP_InputConfigData* InputActions;

private:
	/** Delegate this movement logic to the possessed Pawn class. */
	void Move(const FInputActionValue& Value);

	/** Delegate this dash movement logic to the possessed Pawn class. */
	void Dash(const FInputActionValue& Value);

	/** Delegate this taunt logic to the possessed Pawn class. */
	void Taunt(const FInputActionValue& Value);

	/** Delegate this cancel taunt logic to the possessed Pawn class. */
	void CancelTaunt(const FInputActionValue& Value);

#pragma endregion 
	
};
