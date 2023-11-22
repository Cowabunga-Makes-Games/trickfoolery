// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/TimelineComponent.h"
#include "CPP_InputConfigData.h"
#include "CPP_Player.generated.h"

UENUM(BlueprintType)
enum ETauntType {
	Bleh
	UMETA(DisplayName="Bleh"),
	CrabFace
	UMETA(DisplayName="CrabFace"),
	LobsterRoll
	UMETA(DisplayName="LobsterRoll"),
	TauntCount
};

//*******************************************************************************************
// CPP_Player
//*******************************************************************************************
/**
 * Extends the ACharacter class to implement core player movement, dash, and taunt
 * mechanics.
 */
UCLASS()
class TRICKFOOLERY_API ACPP_Player : public ACharacter {
	GENERATED_BODY()

#pragma region UE Methods
	
public:
	// Sets default values for this character's properties
	ACPP_Player();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

#pragma endregion

#pragma region Input

#pragma region Movement
	
public:
	/** Moves this character's position according to input scaled by MovementSpeed. */
	void Move(const FInputActionValue& Value);

	/**
	 * Plays all accessory sound, visual, etc. effects associated with this character movement via a Blueprint event.
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = "Player Movement")
		void PlayMovementEffects();

protected:
	/** The speed multiplier for the movement in the level. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Movement")
		float MovementSpeed;

#pragma endregion

#pragma region Dash

public:
	/** Applies a force to this character along the forward direction according to input scaled by DashForce. */
	void Dash(const FInputActionValue& Value);

	/**
	 * Plays all accessory sound, visual, etc. effects associated with this character's dash movement via a Blueprint
	 * event.
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = "Player Dash")
		void PlayDashEffects();

	/**
	 * Invoked on every update to the DashTimeline. Applies the dash movement velocity to the character according to
	 * the DashCurve.
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = "Player Dash")
		void OnDashTimelineUpdate(const float Value);

protected:
	/** The timeline to adjust this character's velocity and sync dash animation over a duration of time. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Dash")
		UTimelineComponent* DashTimeline;

	/** The float curve used to model this character's changing velocity over the DashTimeline duration of time. */
	UPROPERTY(EditAnywhere, Category = "Player Dash")
		UCurveFloat* DashCurve;

	/** Adjusts this character's distance and speed attained within a single dash execution. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Dash")
		float DashDistance;

private:
	bool CanDash;

	/** Handles when the DashTimeline is completed. Toggles the CanDash flag to re-enable the dash ability. */
	UFUNCTION()
		void OnDashTimelineComplete();

#pragma endregion

#pragma region Taunt

public:
	/** If a taunt is not already in progress, begins a new taunt. */
	void Taunt(const FInputActionValue& Value);

	/** Cancels the taunt currently being executed. */
	void CancelTaunt(const FInputActionValue& Value);

	/** Plays all accessory sound, visual, etc. effects associated with this character's taunts via a Blueprint event. */
	UFUNCTION(BlueprintImplementableEvent, Category = "Player Taunt")
		void PlayTauntEffects();

	/** Quits all accessory sound, visual, etc. effects associated with the current taunt via a Blueprint event. */
	UFUNCTION(BlueprintImplementableEvent, Category = "Player Taunt")
		void CancelTauntEffects();

protected:
	/** Corresponds to the taunt types available to the player, used to trigger various SFX and timelines. */
	UPROPERTY(BlueprintReadOnly, Category = "Player Taunt")
		TEnumAsByte<ETauntType> TauntType;

	/** Adjusts this character's distance and speed attained within a single dash execution. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Taunt")
		TArray<float> TauntExecutionCooldown;

private:
	bool IsTaunting, CanTaunt;

	/** Refers to the current timer associated with the taunt execution chain. */
	FTimerHandle TauntTimeHandler;

	/** Handles when the taunt execution timer is completed. Toggles the CanTaunt flag to re-enable the taunt ability. */
	void OnTauntComplete();

#pragma endregion

#pragma endregion 

};
