// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Player.h"

#pragma region UE Methods

// Sets default values
ACPP_Player::ACPP_Player() {
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACPP_Player::BeginPlay() {
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_Player::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACPP_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Add the pointer to the UInputMappingContext to the Engine's Subsystem for the LocalPlayer to use
	const APlayerController* PlayerController = Cast<APlayerController>(GetController());

	// Get the local player subsystem, clear the existing mappings, and add our own mapping
	UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem> (PlayerController -> GetLocalPlayer());

	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMapping, 0);

	UEnhancedInputComponent* PEI = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	// Bind all Input Actions here
	PEI->BindAction(InputActions->MovementInput, ETriggerEvent::Triggered, this, &ACPP_Player::Move);
}

#pragma endregion

#pragma region Input

void ACPP_Player::Move(const FInputActionValue& Value) {
	if (Controller == nullptr) return;
	
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
}

#pragma endregion