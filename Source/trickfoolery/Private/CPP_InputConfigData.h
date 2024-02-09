// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputAction.h"
#include "CPP_InputConfigData.generated.h"

//*******************************************************************************************
// CPP_InputConfigData
//*******************************************************************************************
/**
 * A Data Asset utilized to store all references to Input Actions used in IMC_Player
 * to bind to Actor-specific action methods.
 */
UCLASS()
class UCPP_InputConfigData : public UDataAsset {
	GENERATED_BODY()

public:
	/** Governs the player character movement input. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UInputAction* MovementInput;

	/** Governs the player character dash input. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UInputAction* DashInput;

	/** Governs when the player character receives input to taunt. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UInputAction* TauntInput;

	/** Governs when the player character stops receiving input to taunt, cancelling the taunt. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UInputAction* CancelTauntInput;
		
    /** TODO: Remove this when linking the health UI to the enemy-to-player damage response. */
        UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
            UInputAction* DepleteHealthInput;
};
