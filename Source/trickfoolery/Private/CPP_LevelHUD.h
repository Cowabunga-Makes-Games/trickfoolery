// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_PlayerHealthWidget.h"
#include "GameFramework/HUD.h"
#include "CPP_LevelHUD.generated.h"

//*******************************************************************************************
// CPP_LevelHUD
//*******************************************************************************************
/**
 * Manages all widget component references associated with the HUD to be displayed during
 * an arena level that are to be exposed to core Cpp classes for event-based UI updates.
 */
UCLASS()
class ACPP_LevelHUD : public AHUD {
	GENERATED_BODY()

public:
	/** References to the widgets associated with this HUD to expose for reference in Cpp classes. */
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget Components")
		UCPP_PlayerHealthWidget* PlayerHealthWidget;
};
