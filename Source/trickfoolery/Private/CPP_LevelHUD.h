// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_PlayerHealthWidget.h"
#include "GameFramework/HUD.h"
#include "CPP_LevelHUD.generated.h"

/**
 * 
 */
UCLASS()
class ACPP_LevelHUD : public AHUD {
	GENERATED_BODY()

public:
	/** References to the widgets associated with this HUD. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget Components")
		UCPP_PlayerHealthWidget* PlayerHealthWidget;
};
