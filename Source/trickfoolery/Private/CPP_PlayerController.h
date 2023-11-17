// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "CPP_Player.h"
#include "CPP_PlayerController.generated.h"

//*******************************************************************************************
// ACPP_PlayerController
//*******************************************************************************************
/// <summary>
/// Links the Enhanced Input System bindings to the active possessed Pawn.
/// </summary>
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
	/// Handle setting up the Input Mapping Context in the PlayerController and delegate the action binded method logic
	/// to the possessed Pawn to support the repossession of a Pawn at any given time. (if we want to go that route...)

	protected:
	/// <summary>
	/// Reference to the UInputMappingContext to be used to receive player input.
	/// <summary>
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputMappingContext* InputMappingContext;
	
	/// <summary>
	/// Reference to the defined InputActions to bind input events to this character's methods.
	/// <summary>
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UCPP_InputConfigData* InputActions;

private:
	/// <summary>
	/// Delegate this movement logic to the possessed Pawn class.
	/// <summary>
	void Move(const FInputActionValue& Value);

	/// <summary>
	/// Delegate this dash movement logic to the possessed Pawn class.
	/// <summary>
	void Dash(const FInputActionValue& Value);
	
	/// <summary>
	/// Delegate this taunt logic to the possessed Pawn class.
	/// <summary>
	void Taunt(const FInputActionValue& Value);

	/// <summary>
	/// Delegate this cancel taunt logic to the possessed Pawn class.
	/// <summary>
	void CancelTaunt(const FInputActionValue& Value);

#pragma endregion 
	
};
