// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Player.h"

#include "Kismet/KismetSystemLibrary.h"

#pragma region UE Methods

// Sets default values
ACPP_Player::ACPP_Player() {
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CanDash = true;
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

void ACPP_Player::Move(const FInputActionValue& Value) {
	if (!CanDash || Controller == nullptr) return;
	
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

void ACPP_Player::Dash(const FInputActionValue& Value) {
	if (!CanDash || Controller == nullptr) return;

	DashTimeline->PlayFromStart();
	
	// Cancel the current taunt action if applicable and can dash
	PlayDashEffects();
	
	CanDash = false;
}

void ACPP_Player::OnDashTimelineComplete() {
	CanDash = true;
}

void ACPP_Player::Taunt(const FInputActionValue& Value) {
	UKismetSystemLibrary::PrintString(this, "Hey! CRABFACE!!!");
}

void ACPP_Player::CancelTaunt(const FInputActionValue& Value) {
	UKismetSystemLibrary::PrintString(this, "Cancel Taunt");
}

#pragma endregion