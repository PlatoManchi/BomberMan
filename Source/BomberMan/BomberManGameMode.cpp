// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "BomberManGameMode.h"
#include "Camera/BomberManCamera.h"
#include "Characters/BomberManPlayerState.h"
#include "Characters/BomberManCharacter.h"
#include "Gameplay/LevelCreator.h"
#include "Gameplay/Pickups/BasePickup.h"
#include "UI/InGameHUDWidget.h"
#include "UI/ResetMenuWidget.h"

// Engine includes
#include "EngineUtils.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"



ABomberManGameMode::ABomberManGameMode() :
	InGameHUD(nullptr),
	IsPlayer1Dead(false),
	IsPlayer2Dead(false),
	IsRoundOver(true),
	RoundEndTimeElapsed(-1.0f),
	ResetMenuHUD(nullptr),
	MainMenuHUD(nullptr),
	Player1Score(0),
	Player2Score(0),
	MaxRoundPlayTime(180),
	RoundPlayTimeElapsed(0)
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;

	// Set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Characters/BP_BomberManCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// Set default controller class to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<AController> PlayerControllerBPClass(TEXT("/Game/Blueprints/Characters/BP_BomberManController"));
	if (PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}

	// Set default player state class
	PlayerStateClass = ABomberManPlayerState::StaticClass();

	// Set default controller class to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<UUserWidget> InGameHUDBPClass(TEXT("/Game/Blueprints/UI/InGameHUD/WBP_InGameHUDWidget"));
	if (InGameHUDBPClass.Class != NULL)
	{
		InGameHUDClass = InGameHUDBPClass.Class;
	}
	
	// Set default controller class to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<UUserWidget> MainMenuHUDBPClass(TEXT("/Game/Blueprints/UI/WBP_MainMenuWidget"));
	if (MainMenuHUDBPClass.Class != NULL)
	{
		MainMenuHUDClass = MainMenuHUDBPClass.Class;
	}
	
	// Set default controller class to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<UUserWidget> ResetHUDBPClass(TEXT("/Game/Blueprints/UI/WBP_ResetMenuWidget"));
	if (ResetHUDBPClass.Class != NULL)
	{
		ResetHUDClass = ResetHUDBPClass.Class;
	}
}

void ABomberManGameMode::BeginPlay()
{
	// Creating another player so that there are two players
	UGameplayStatics::CreatePlayer(GetWorld(), 1);

	// Getting the camera from world and setting it as the camera to be used as target to render.
	TActorIterator<ABomberManCamera> itr(GetWorld());
	if (itr)
	{
		ABomberManCamera* bombermanCamera = *itr;
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetViewTargetWithBlend(bombermanCamera);
	}

	ResetMenuHUD = CreateWidget<UResetMenuWidget>(GetWorld(), ResetHUDClass);
	
	MainMenuHUD = CreateWidget<UUserWidget>(GetWorld(), MainMenuHUDClass);
	MainMenuHUD->SetVisibility(ESlateVisibility::Visible);
	
	MainMenuHUD->AddToViewport();

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeUIOnly());

	ResetMenuHUD->AddToViewport();
	ResetMenuHUD->SetVisibility(ESlateVisibility::Hidden);
}

void ABomberManGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsRoundOver)
	{
		RoundPlayTimeElapsed += DeltaTime;
		if (RoundPlayTimeElapsed >= MaxRoundPlayTime)
		{
			IsRoundOver = true;
			RoundEndTimeElapsed = 0.0f;
			ResetMenuHUD->SetWinningTeam(-1);
		}

		InGameHUD->SetTimer(MaxRoundPlayTime - RoundPlayTimeElapsed);

		if (IsPlayer1Dead || IsPlayer2Dead)
		{
			IsRoundOver = true;
			
			RoundEndTimeElapsed = 2.0f;

			if (IsPlayer1Dead && IsPlayer2Dead)
			{
				ResetMenuHUD->SetWinningTeam(-1);
			}
			else if (IsPlayer1Dead)
			{
				Player2Score++;
				ResetMenuHUD->SetWinningTeam(1);
			}
			else if (IsPlayer2Dead)
			{
				Player1Score++;
				ResetMenuHUD->SetWinningTeam(0);
			}
		}
	}
	

	if (IsRoundOver && RoundEndTimeElapsed >= 0.0f)
	{
		RoundEndTimeElapsed -= DeltaTime;

		if (RoundEndTimeElapsed <= 0.0f)
		{
			if (ResetMenuHUD && ResetMenuHUD->GetVisibility() != ESlateVisibility::Visible)
			{
				ResetMenuHUD->UpdateScore();
				InGameHUD->SetVisibility(ESlateVisibility::Hidden);

				ResetMenuHUD->SetVisibility(ESlateVisibility::Visible);

				UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;
				UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeUIOnly());
			}
		}
	}
}

void ABomberManGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (!InGameHUD)
	{
		UE_LOG(LogTemp, Warning, TEXT("Creating hud"));
		InGameHUD = CreateWidget<UInGameHUDWidget>(GetWorld(), InGameHUDClass);
		InGameHUD->AddToViewport();
		InGameHUD->SetVisibility(ESlateVisibility::Hidden);
	}

	if (NewPlayer && InGameHUD)
	{
		ABomberManPlayerState* playerState = Cast<ABomberManPlayerState>(NewPlayer->PlayerState);
		ABomberManCharacter* character = Cast<ABomberManCharacter>(NewPlayer->GetPawn());
		
		// Initializing the player
		if (playerState)
		{
			playerState->PlayerID = UGameplayStatics::GetPlayerControllerID(NewPlayer);
			playerState->Reset();

			// Setting up UI.
			if (character)
			{
				if (playerState->PlayerID == 0)
				{
					InGameHUD->SetPlayer1(character);
				}

				if (playerState->PlayerID == 1)
				{
					InGameHUD->SetPlayer2(character);
				}
			}
		}
	}
}

void ABomberManGameMode::ResetScore()
{
	Player1Score = 0.0f;
	Player2Score = 0.0f;
}


void ABomberManGameMode::PlayerDead(int32 PlayerID)
{
	if (PlayerID == 0)
	{
		IsPlayer1Dead = true;
	}
	if (PlayerID == 1)
	{
		IsPlayer2Dead = true;
	}
}

void ABomberManGameMode::Reset()
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeGameOnly());
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = false;

	if(InGameHUD) InGameHUD->SetVisibility(ESlateVisibility::Visible);
	if(ResetMenuHUD) ResetMenuHUD->SetVisibility(ESlateVisibility::Hidden);
	if(MainMenuHUD) MainMenuHUD->SetVisibility(ESlateVisibility::Hidden);

	IsRoundOver = false;
	RoundPlayTimeElapsed = 0;

	IsPlayer1Dead = false;
	IsPlayer2Dead = false;

	for (TActorIterator<AController> itr(GetWorld()); itr; ++itr)
	{
		AController* controller = *itr;
		ABomberManPlayerState* playerstate = Cast<ABomberManPlayerState>(controller->PlayerState);
		playerstate->Reset();
	}

	for (TActorIterator<ABomberManCharacter> itr(GetWorld()); itr; ++itr)
	{
		(*itr)->Reset();
	}

	for (TActorIterator<ALevelCreator> itr(GetWorld()); itr; ++itr)
	{
		(*itr)->ResetLevel();
	}

	if(InGameHUD) InGameHUD->Reset();

	/** Remove all pickups on map
	*/
	for (TActorIterator<ABasePickup> itr(GetWorld()); itr; ++itr)
	{
		(*itr)->Destroy();
	}
}

void ABomberManGameMode::ShowMainMenu()
{
	MainMenuHUD->SetVisibility(ESlateVisibility::Visible);
	ResetMenuHUD->SetVisibility(ESlateVisibility::Hidden);
}
