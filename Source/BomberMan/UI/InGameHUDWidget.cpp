// Fill out your copyright notice in the Description page of Project Settings.

#include "InGameHUDWidget.h"
#include "Characters/BomberManPlayerState.h"

void UInGameHUDWidget::NativeTick(const FGeometry & MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (PrevPlayer1MaxBombs != Player1State->MaxBombsAvailable)
	{
		SetPlayer1MaxBombs(Player1State->MaxBombsAvailable);
		PrevPlayer1MaxBombs = Player1State->MaxBombsAvailable;
	}

	if (PrevPlayer1CurrentBombs != Player1State->CurrentBombsAvailable)
	{
		SetPlayer1CurrentBombs(Player1State->CurrentBombsAvailable);
		PrevPlayer1CurrentBombs = Player1State->CurrentBombsAvailable;
	}

	if (PrevPlayer2MaxBombs != Player2State->MaxBombsAvailable)
	{
		SetPlayer2MaxBombs(Player2State->MaxBombsAvailable);
		PrevPlayer2MaxBombs = Player2State->MaxBombsAvailable;
	}

	if (PrevPlayer2CurrentBombs != Player2State->CurrentBombsAvailable)
	{
		SetPlayer2CurrentBombs(Player2State->CurrentBombsAvailable);
		PrevPlayer2CurrentBombs = Player2State->CurrentBombsAvailable;
	}
}


void UInGameHUDWidget::SetPlayer1State(ABomberManPlayerState* PlayerState)
{
	Player1State = PlayerState;

	SetPlayer1MaxBombs(Player1State->MaxBombsAvailable);
	SetPlayer1CurrentBombs(Player1State->CurrentBombsAvailable);

	PrevPlayer1MaxBombs = Player1State->MaxBombsAvailable;
	PrevPlayer1CurrentBombs = Player1State->CurrentBombsAvailable;
}

void UInGameHUDWidget::SetPlayer2State(ABomberManPlayerState* PlayerState)
{
	Player2State = PlayerState;

	SetPlayer2MaxBombs(Player2State->MaxBombsAvailable);
	SetPlayer2CurrentBombs(Player2State->CurrentBombsAvailable);

	PrevPlayer2MaxBombs = Player2State->MaxBombsAvailable;
	PrevPlayer2CurrentBombs = Player2State->CurrentBombsAvailable;
}

