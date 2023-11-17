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

#pragma region Movement
	
public:
	/// <summary>
	/// Moves this character's position according to input scaled by MovementSpeed.
	/// <summary>
	void Move(const FInputActionValue& Value);
	
	/// <summary>
	/// Plays all accessory sound, visual, etc. effects associated with this character movement via a Blueprint event.
	/// <summary>
	UFUNCTION(BlueprintImplementableEvent, Category = "Player Movement")
		void PlayMovementEffects();

protected:
	/// <summary>
	/// The speed multiplier for the movement in the level.
	/// <summary>
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Movement")
		float MovementSpeed;

#pragma endregion

#pragma region Dash

public:
	/// <summary>
	/// Applies a force to this character along the forward direction according to input scaled by DashForce.
	/// <summary>
	void Dash(const FInputActionValue& Value);
	
	/// <summary>
	/// Plays all accessory sound, visual, etc. effects associated with this character's dash movement via a
	/// Blueprint event.
	/// <summary>
	UFUNCTION(BlueprintImplementableEvent, Category = "Player Dash")
		void PlayDashEffects();

	/// <summary>
	/// Invoked on every update to the DashTimeline. Applies the dash movement velocity to the character according to
	/// the DashCurve.
	/// <summary>
	UFUNCTION(BlueprintImplementableEvent, Category = "Player Dash")
		void OnDashTimelineUpdate(const float Value);

protected:
	/// <summary>
	/// The timeline to adjust this character's velocity and sync dash animation over a duration of time.
	/// <summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Dash")
	UTimelineComponent* DashTimeline;
	
	/// <summary>
	/// The float curve used to model this character's changing velocity over the DashTimeline duration of time.
	/// <summary>
	UPROPERTY(EditAnywhere, Category = "Player Dash")
		UCurveFloat* DashCurve;
	
	/// <summary>
	/// Adjusts this character's distance and speed attained within a single dash execution.
	/// <summary>
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Dash")
		float DashDistance;

private:
	bool CanDash;
	
	/// <summary>
	/// Handles when the DashTimeline is completed. Toggles the CanDash flag to re-enable the dash ability.
	/// <summary>
	UFUNCTION()
		void OnDashTimelineComplete();

#pragma endregion

#pragma region Taunt

public:
	/// <summary>
	/// If a taunt is not already in progress, begins a new taunt.
	/// <summary>
	void Taunt(const FInputActionValue& Value);

	/// <summary>
	/// Cancels the taunt currently being executed.
	/// <summary>
	void CancelTaunt(const FInputActionValue& Value);

	/// <summary>
	/// Plays all accessory sound, visual, etc. effects associated with this character's taunts via a Blueprint event.
	/// <summary>
	UFUNCTION(BlueprintImplementableEvent, Category = "Player Taunt")
	void PlayTauntEffects();

	/// <summary>
	/// Quits all accessory sound, visual, etc. effects associated with the current taunt via a Blueprint event.
	/// <summary>
	UFUNCTION(BlueprintImplementableEvent, Category = "Player Taunt")
	void CancelTauntEffects();

protected:
	/// <summary>
	/// Corresponds to the taunt types available to the player, used to trigger various SFX and timelines.
	/// <summary>
	UPROPERTY(BlueprintReadOnly, Category = "Player Taunt")
		TEnumAsByte<ETauntType> TauntType;

	/// <summary>
	/// Adjusts this character's distance and speed attained within a single dash execution.
	/// <summary>
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Taunt")
		TArray<float> TauntExecutionCooldown;

private:
	bool CanTaunt;

	/// <summary>
	/// Refers to the current timer associated with the taunt execution chain.
	/// <summary>
	FTimerHandle TauntTimeHandler;

	/// <summary>
	/// Handles when the taunt execution timer is completed. Toggles the CanTaunt flag to re-enable the taunt ability.
	/// <summary>
	void OnTauntComplete();

#pragma endregion

#pragma endregion 

};
