// Fill out your copyright notice in the Description page of Project Settings.

#include "BomberManController.h"
#include "BomberManCharacter.h"

void ABomberManController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	// Caching the character so that character is available
	BomberManCharacter = Cast<ABomberManCharacter>(InPawn);
}

void ABomberManController::SetupInputComponent()
{
	// Set up gameplay key bindings
	Super::SetupInputComponent();
	check(InputComponent);

	int32 id = GetLocalPlayer()->GetControllerId();
	if (id == 0)
	{
		InputComponent->BindAxis("MoveForward_P1", this, &ABomberManController::MoveForward);
		InputComponent->BindAxis("MoveRight_P1", this, &ABomberManController::MoveRight);

		InputComponent->BindAction("PlaceBomb_P1", EInputEvent::IE_Released, this, &ABomberManController::PlaceBomb);
	}
	else if (id == 1)
	{
		InputComponent->BindAxis("MoveForward_P2", this, &ABomberManController::MoveForward);
		InputComponent->BindAxis("MoveRight_P2", this, &ABomberManController::MoveRight);

		InputComponent->BindAction("PlaceBomb_P2", EInputEvent::IE_Released, this, &ABomberManController::PlaceBomb);
	}
}

void ABomberManController::MoveForward(float Value)
{
	if (BomberManCharacter)
	{
		BomberManCharacter->MoveForward(Value);
	}
}

void ABomberManController::MoveRight(float Value)
{
	if (BomberManCharacter)
	{
		BomberManCharacter->MoveRight(Value);
	}
}

void ABomberManController::PlaceBomb()
{
	if (BomberManCharacter)
	{
		BomberManCharacter->PlaceBomb();
	}
}
