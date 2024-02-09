// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CPP_PlayerHealthWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class UCPP_PlayerHealthWidget : public UUserWidget {
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	/**
	 * Provides lower level access to the blueprint implemented widget update health event.
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = "Player")
		void UpdateHealth(float NewValue);
};
