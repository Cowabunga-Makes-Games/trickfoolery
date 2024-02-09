// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_Player.h"

#include "CPP_LevelHUD.h"
#include "CPP_PlayerController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AISense_Sight.h"

#pragma region UE Methods

// Sets default values
ACPP_Player::ACPP_Player() {
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	bCanDash = true;
	bCanTaunt = true;
	DashTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimelineComponent"));

	SetupStimulusSource();
}

// Called when the game starts or when spawned
void ACPP_Player::BeginPlay() {
	Super::BeginPlay();
	
	if (DashCurve) {
		// Delegate, contains the signature of the function to execute on every DashTimeline update
		FOnTimelineFloat timelineUpdateCallback;
		FOnTimelineEventStatic timelineFinishedCallback;

		timelineUpdateCallback.BindUFunction(this, FName{ TEXT("OnDashTimelineUpdate") });
		timelineFinishedCallback.BindUFunction(this, FName{ TEXT("OnDashTimelineComplete") });

		// Set up loop status and the function that will fire when the timeline ticks
		DashTimeline->SetTimelineLength(0.8f);
		DashTimeline->AddInterpFloat(DashCurve, timelineUpdateCallback);
		DashTimeline->SetTimelineFinishedFunc(timelineFinishedCallback);
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

#pragma region AI Perception System

void ACPP_Player::SetupStimulusSource() {
	StimulusSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus Source"));
	
	StimulusSource->RegisterForSense(TSubclassOf<UAISense_Sight>());
	StimulusSource->RegisterForSense(TSubclassOf<UAISense_Hearing>());
	StimulusSource->RegisterWithPerceptionSystem();
}

#pragma endregion

#pragma region Input

#pragma region Movement

void ACPP_Player::Move(const FInputActionValue& Value) {
	if (!bCanDash || bIsTaunting || Controller == nullptr) return;
	
	const FVector2D vInput = Value.Get<FVector2D>();
	if (vInput.IsZero()) return;
	
	const FRotator controlRotation(0, Controller->GetControlRotation().Yaw, 0);
	const float deltaSeconds = GetWorld()->GetDeltaSeconds();

	// Forward/Backward direction
	if (vInput.Y != 0.f) {
		// Get forward vector
		const FVector direction = controlRotation.RotateVector(FVector::ForwardVector);
		
		AddMovementInput(direction * deltaSeconds, vInput.Y * MovementSpeed);
	}

	// Right/Left direction
	if (vInput.X != 0.f) {
		// Get right vector
		const FVector direction = controlRotation.RotateVector(FVector::RightVector);
		
		AddMovementInput(direction * deltaSeconds, vInput.X * MovementSpeed);
	}
	
	PlayMovementEffects(vInput);
}

#pragma endregion

#pragma region Dash

void ACPP_Player::Dash(const FInputActionValue& Value) {
	if (!bCanDash || Controller == nullptr) return;

	DashTimeline->PlayFromStart();
	
	// Cancel the current taunt action
	if (bIsTaunting) {
		CancelTaunt(0);
	}
	
	PlayDashEffects();
	
	bCanDash = false;
}

void ACPP_Player::OnDashTimelineComplete() {
	bCanDash = true;
	bCanTaunt = true;
}

#pragma endregion 

#pragma region Taunt

void ACPP_Player::Taunt(const FInputActionValue& Value) {
	if (!bCanTaunt) return;

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
	bIsTaunting = true;
	bCanTaunt = false;
}

// Can be used to increment some taunt combo to add hype or angy multipliers
void ACPP_Player::OnTauntComplete() {
	bCanTaunt = true;

	UKismetSystemLibrary::PrintString(this, "Taunt complete!");
}

void ACPP_Player::CancelTaunt(const FInputActionValue& Value) {
	UKismetSystemLibrary::PrintString(this, "Cancel Taunt Execution Chain");

	GetWorldTimerManager().ClearTimer(TauntTimeHandler);
	CancelTauntEffects();
	bIsTaunting = false;
	bCanTaunt = true;
}

#pragma endregion

void ACPP_Player::DepleteHealth(const FInputActionValue& Value) {
	if (Controller == nullptr || FMath::IsNearlyEqual(Health, 0.0f)) return;

	Health -= 1.0f;

	const ACPP_PlayerController* controller = Cast<ACPP_PlayerController>(Controller);
	if (controller == nullptr) {
		return;
	}

	const ACPP_LevelHUD* HUD = Cast<ACPP_LevelHUD>(controller->GetHUD());
	if (HUD == nullptr) {
		return;
	}

	HUD->PlayerHealthWidget->UpdateHealth(Health);
}

#pragma endregion