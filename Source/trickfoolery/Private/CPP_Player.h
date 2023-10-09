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
	/// Applies a force to this character along the forward direction according to input scaled by DashForce.
	/// <summary>
	void Dash(const FInputActionValue& Value);
	
	/// <summary>
	/// Plays all accessory sound, visual, etc. effects associated with this character's dash movement via a
	/// Blueprint event.
	/// <summary>
	UFUNCTION(BlueprintImplementableEvent, Category = "Enhanced Input")
	void PlayDashEffects();
	
	/// <summary>
	/// Moves this character's position according to input scaled by MovementSpeed.
	/// <summary>
	void Move(const FInputActionValue& Value);
	
	/// <summary>
	/// Plays all accessory sound, visual, etc. effects associated with this character movement via a Blueprint event.
	/// <summary>
	UFUNCTION(BlueprintImplementableEvent, Category = "Enhanced Input")
		void PlayMovementEffects();

	void BindActions(UEnhancedInputComponent* EnhancedInputComponent);

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

	/// <summary>
	/// The force multiplier for the dash movement in the level.
	/// <summary>
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
		float DashForce;

	/// <summary>
	/// The duration of time required to pass between dash ability executions.
	/// <summary>
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
		float DashCooldown;

private:
	
	/// <summary>
	/// Refers to the current timer associated with the dash cooldown.
	/// <summary>
	FTimerHandle DashCooldownTimeHandler;
	
	bool CanDash;

	/// <summary>
	/// Handles when the dash cooldown timer is completed. Toggles the CanDash flag to enable the dash ability.
	/// <summary>
	void OnDashCooldownComplete();

#pragma endregion 

};
