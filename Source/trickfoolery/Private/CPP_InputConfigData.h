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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UInputAction* MovementInput;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UInputAction* DashInput;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UInputAction* TauntInput;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UInputAction* CancelTauntInput;
};
