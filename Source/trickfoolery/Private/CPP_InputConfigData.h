// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputAction.h"
#include "CPP_InputConfigData.generated.h"

//*******************************************************************************************
// UCPP_InputConfigData
//*******************************************************************************************
/// <summary>
/// A Data Asset utilized to store all references to Input Actions used in IMC_Player
/// to bind to Actor-specific action methods.
/// </summary>
UCLASS()
class TRICKFOOLERY_API UCPP_InputConfigData : public UDataAsset {
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UInputAction* MovementInput;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UInputAction* DashInput;
};
