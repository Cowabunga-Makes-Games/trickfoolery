// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_Player.h"
#include "Kismet/KismetSystemLibrary.h"

#pragma region UE Methods

// Sets default values
ACPP_Player::ACPP_Player() {
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CanDash = true;
	CanTaunt = true;
	DashTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimelineComponent"));
}

// Called when the game starts or when spawned
void ACPP_Player::BeginPlay() {
	Super::BeginPlay();
	
	if (DashCurve) {
		// Delegate, contains the signature of the function to execute on every DashTimeline update
		FOnTimelineFloat TimelineUpdateCallback;
		FOnTimelineEventStatic TimelineFinishedCallback;

		TimelineUpdateCallback.BindUFunction(this, FName{ TEXT("OnDashTimelineUpdate") });
		TimelineFinishedCallback.BindUFunction(this, FName{ TEXT("OnDashTimelineComplete") });

		// Set up loop status and the function that will fire when the timeline ticks
		DashTimeline->SetTimelineLength(0.8f);
		DashTimeline->AddInterpFloat(DashCurve, TimelineUpdateCallback);
		DashTimeline->SetTimelineFinishedFunc(TimelineFinishedCallback);
		DashTimeline->SetLooping(false);

		return;
	}

	UE_LOG(LogTemp, Error, TEXT("No DashCurve is assigned! Aborting dash mechanic setup."))
}

// Called every frame
void ACPP_Player::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	
	if (DashTimeline->IsPlaying()) {
		DashTimeline->TickComponent(DeltaTime, LEVELTICK_TimeOnly, NULL);
	}
}

// Called to bind functionality to input
void ACPP_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

#pragma endregion

#pragma region Input

#pragma region Movement

void ACPP_Player::Move(const FInputActionValue& Value) {
	if (!CanDash || IsTaunting || Controller == nullptr) return;
	
	const FVector2D InputVector = Value.Get<FVector2D>();
	const FRotator ControlRotation(0, Controller->GetControlRotation().Yaw, 0);

	// Forward/Backward direction
	if (InputVector.Y != 0.f) {
		// Get forward vector
		const FVector Direction = ControlRotation.RotateVector(FVector::ForwardVector);
		
		AddMovementInput(Direction, InputVector.Y * MovementSpeed);
	}

	// Right/Left direction
	if (InputVector.X != 0.f) {
		// Get right vector
		const FVector Direction = ControlRotation.RotateVector(FVector::RightVector);
		
		AddMovementInput(Direction, InputVector.X * MovementSpeed);
	}
	
	PlayMovementEffects();
}

#pragma endregion

#pragma region Dash

void ACPP_Player::Dash(const FInputActionValue& Value) {
	if (!CanDash || Controller == nullptr) return;

	DashTimeline->PlayFromStart();
	
	// Cancel the current taunt action
	if (IsTaunting) {
		CancelTaunt(0);
	}
	
	PlayDashEffects();
	
	CanDash = false;
}

void ACPP_Player::OnDashTimelineComplete() {
	CanDash = true;
	CanTaunt = true;
}

#pragma endregion 

#pragma region Taunt

void ACPP_Player::Taunt(const FInputActionValue& Value) {
	if (!CanTaunt) return;

	// Select a random taunt type
	TauntType = static_cast<ETauntType>(FMath::RandRange(0, TauntCount - 1));

	// TODO: Timer implementation can be changed to a Timeline in the future if we'd like to attach a curve to it to
	// simulate taunt "keywords" that increase angy stats at a higher rate at certain points in the sound clips
	GetWorldTimerManager().SetTimer(TauntTimeHandler, this, &ACPP_Player::OnTauntComplete,
		TauntExecutionCooldown[TauntType], false);

	// TODO: Just for testing, remove when actual SFX and animations come in
	switch (TauntType) {
		case (Bleh):
			UKismetSystemLibrary::PrintString(this, "Bleeeeeeeeeh");
			break;
		case (CrabFace):
			UKismetSystemLibrary::PrintString(this, "Hey! CRABFACE!!!");
			break;
		case (LobsterRoll):
			UKismetSystemLibrary::PrintString(this, "Hey! LOBSTER ROLL!!!");
			break;
		default:
			break;
	}
	
	PlayTauntEffects();
	IsTaunting = true;
	CanTaunt = false;
}

// Can be used to increment some taunt combo to add hype or angy multipliers
void ACPP_Player::OnTauntComplete() {
	CanTaunt = true;

	UKismetSystemLibrary::PrintString(this, "Taunt complete!");
}

void ACPP_Player::CancelTaunt(const FInputActionValue& Value) {
	UKismetSystemLibrary::PrintString(this, "Cancel Taunt Execution Chain");

	GetWorldTimerManager().ClearTimer(TauntTimeHandler);
	CancelTauntEffects();
	IsTaunting = false;
	CanTaunt = true;
}

#pragma endregion 

#pragma endregion