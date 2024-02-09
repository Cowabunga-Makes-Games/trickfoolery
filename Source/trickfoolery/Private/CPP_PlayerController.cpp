// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_PlayerController.h"

#pragma region UE Methods

ACPP_PlayerController::ACPP_PlayerController() {
	// InputMappingContext and InputActions to be initialized and set in the Blueprint of the same name
}

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
		EnhancedInputComponent->BindAction(InputActions->TauntInput, ETriggerEvent::Triggered, this, &ACPP_PlayerController::Taunt);
		EnhancedInputComponent->BindAction(InputActions->CancelTauntInput, ETriggerEvent::Triggered, this, &ACPP_PlayerController::CancelTaunt);
		EnhancedInputComponent->BindAction(InputActions->DepleteHealthInput, ETriggerEvent::Triggered, this, &ACPP_PlayerController::DepleteHealth);
		EnhancedInputComponent->BindAction(InputActions->AddHealthInput, ETriggerEvent::Triggered, this, &ACPP_PlayerController::AddHealth);
	}
}

#pragma endregion

#pragma region Input

void ACPP_PlayerController::Move(const FInputActionValue& Value) {
	if (auto possessedPawn = Cast<ACPP_Player>(this->GetPawn())) {
		possessedPawn->Move(Value);
	}
}

void ACPP_PlayerController::Dash(const FInputActionValue& Value) {
	if (auto possessedPawn = Cast<ACPP_Player>(this->GetPawn())) {
		possessedPawn->Dash(Value);
	}
}

void ACPP_PlayerController::Taunt(const FInputActionValue& Value) {
	if (const auto possessedPawn = Cast<ACPP_Player>(this->GetPawn())) {
		possessedPawn->Taunt(Value);
	}
}

void ACPP_PlayerController::CancelTaunt(const FInputActionValue& Value) {
	if (const auto possessedPawn = Cast<ACPP_Player>(this->GetPawn())) {
		possessedPawn->CancelTaunt(Value);
	}
}

void ACPP_PlayerController::DepleteHealth(const FInputActionValue& Value) {
	if (const auto possessedPawn = Cast<ACPP_Player>(this->GetPawn())) {
		possessedPawn->UpdateHealth(Value, -1.0f);
	}
}

void ACPP_PlayerController::AddHealth(const FInputActionValue& Value) {
	if (const auto possessedPawn = Cast<ACPP_Player>(this->GetPawn())) {
		possessedPawn->UpdateHealth(Value, 0.5f);
	}
}

#pragma endregion

