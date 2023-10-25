// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_PlayerController.h"

#pragma region UE Methods

ACPP_PlayerController::ACPP_PlayerController() {}

void ACPP_PlayerController::BeginPlay() {
	Super::BeginPlay();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer())) {
		Subsystem->ClearAllMappings();
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
}

void ACPP_PlayerController::SetupInputComponent() {
	// Set up gameplay key bindings
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent)) {
		EnhancedInputComponent->BindAction(InputActions->MovementInput, ETriggerEvent::Triggered, this, &ACPP_PlayerController::Move);
		EnhancedInputComponent->BindAction(InputActions->DashInput, ETriggerEvent::Triggered, this, &ACPP_PlayerController::Dash);
	}
}

#pragma endregion

#pragma region Input

void ACPP_PlayerController::Move(const FInputActionValue& Value) {
	if (auto PossessedPawn = Cast<ACPP_Player>(this->GetPawn())) {
		PossessedPawn->Move(Value);
	}
}

void ACPP_PlayerController::Dash(const FInputActionValue& Value) {
	if (auto PossessedPawn = Cast<ACPP_Player>(this->GetPawn())) {
		PossessedPawn->Dash(Value);
	}
}

#pragma endregion

