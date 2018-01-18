// Fill out your copyright notice in the Description page of Project Settings.

#include "InGameHUDWidget.h"
#include "Characters/BomberManPlayerState.h"
#include "Characters/BomberManCharacter.h"

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

	// Remote bombs
	if (IsPlayer1RemoteBomb)
	{
		Player1RemoteBombTimeElapsed += InDeltaTime;
		if (Player1RemoteBombTimeElapsed > Player1RemoteBombMaxTime)
		{
			Player1RemoteBombHide();
		}
	}

	if (IsPlayer2RemoteBomb)
	{
		Player2RemoteBombTimeElapsed += InDeltaTime;
		if (Player2RemoteBombTimeElapsed > Player2RemoteBombMaxTime)
		{
			Player2RemoteBombHide();
		}
	}
}


void UInGameHUDWidget::SetPlayer1(ABomberManCharacter* Player)
{
	ABomberManPlayerState* PlayerState = Cast<ABomberManPlayerState>(Player->GetController()->PlayerState);

	Player1State = PlayerState;
	IsPlayer1RemoteBomb = false;

	SetPlayer1MaxBombs(Player1State->MaxBombsAvailable);
	SetPlayer1CurrentBombs(Player1State->CurrentBombsAvailable);

	PrevPlayer1MaxBombs = Player1State->MaxBombsAvailable;
	PrevPlayer1CurrentBombs = Player1State->CurrentBombsAvailable;

	Player->OnRemoteBombPickup.AddDynamic(this, &UInGameHUDWidget::Player1RemoteBomb);
}

void UInGameHUDWidget::SetPlayer2(ABomberManCharacter* Player)
{
	ABomberManPlayerState* PlayerState = Cast<ABomberManPlayerState>(Player->GetController()->PlayerState);

	Player2State = PlayerState;
	IsPlayer2RemoteBomb = false;

	SetPlayer2MaxBombs(Player2State->MaxBombsAvailable);
	SetPlayer2CurrentBombs(Player2State->CurrentBombsAvailable);

	PrevPlayer2MaxBombs = Player2State->MaxBombsAvailable;
	PrevPlayer2CurrentBombs = Player2State->CurrentBombsAvailable;

	Player->OnRemoteBombPickup.AddDynamic(this, &UInGameHUDWidget::Player2RemoteBomb);
}

void UInGameHUDWidget::Player1RemoteBomb_Implementation(float MaxTime)
{
	Player1RemoteBombMaxTime = MaxTime;
	Player1RemoteBombTimeElapsed = 0;
	IsPlayer1RemoteBomb = true;
}

void UInGameHUDWidget::Player2RemoteBomb_Implementation(float MaxTime)
{
	Player2RemoteBombMaxTime = MaxTime;
	Player2RemoteBombTimeElapsed = 0;
	IsPlayer2RemoteBomb = true;
}

void UInGameHUDWidget::Player1RemoteBombHide_Implementation()
{
	IsPlayer1RemoteBomb = false;
}

void UInGameHUDWidget::Player2RemoteBombHide_Implementation()
{
	IsPlayer2RemoteBomb = false;
}

void UInGameHUDWidget::Reset_Implementation()
{
	Player1RemoteBombHide();
	Player2RemoteBombHide();
}