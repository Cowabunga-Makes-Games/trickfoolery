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

public:
	/// <summary>
	/// Plays all accessory sound, visual, etc. effects associated with this character movement via a Blueprint event.
	/// <summary>
	UFUNCTION(BlueprintImplementableEvent, Category = "Enhanced Input")
		void PlayMovementEffects();

protected:
	/// <summary>
	/// Reference to the UInputMappingContext to be used to receive player input.
	/// <summary>
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
		UInputMappingContext* InputMapping;
	
	/// <summary>
	/// Reference to the defined InputActions to bind input events to this character's methods.
	/// <summary>
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
		UCPP_InputConfigData* InputActions;
	
	/// <summary>
	/// The speed multiplier for the movement in the level.
	/// <summary>
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
		float MovementSpeed;

private:
	/// <summary>
	/// Moves this character's position according to input scaled by MovementSpeed.
	/// <summary>
	void Move(const FInputActionValue& Value);

#pragma endregion 

};
