// Fill out your copyright notice in the Description page of Project Settings.

#include "BomberManPlayerState.h"

ABomberManPlayerState::ABomberManPlayerState()
{

}

void ABomberManPlayerState::Reset()
{
	// Setting player health
	MaxPlayerHealth = 1.0f;
	PlayerHealth = MaxPlayerHealth;

	// Setting the bombs available
	MaxBombsAvailable = 1;
	CurrentBombsAvailable = MaxBombsAvailable;

	// Speed boost
	IsSpeedBoost = false;
}