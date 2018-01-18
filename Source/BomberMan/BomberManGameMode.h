// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BomberManGameMode.generated.h"

class UInGameHUDWidget;
class UResetMenuWidget;

UCLASS(minimalapi)
class ABomberManGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	/** Default constructor
	*/
	ABomberManGameMode();

	/** Called when player dies.
	*/
	void PlayerDead(int32 PlayerID);

protected:
	// Called once when game starts
	void BeginPlay() override;

	/** Called every frame
	*/
	virtual void Tick(float DeltaTime) override;

	/** Called after a successful login.  This is the first place it is safe to call replicated functions on the PlayerController.
	*	@param NewPlayer A new player controller for the logged in player, NULL if login failed for any reason
	*/
	virtual void PostLogin(APlayerController* NewPlayer) override;

	UFUNCTION(BlueprintCallable, Category = "BomberManGameMode")
	void ResetScore();

	/** Reset entire game.
	*/
	UFUNCTION(BlueprintCallable, Category = "BomberManGameMode")
	void Reset();

	/** Show main menu
	*/
	UFUNCTION(BlueprintCallable, Category = "BomberManGameMode")
	void ShowMainMenu();

	/** Pointer that holds the ingame hud widget
	*/
	UPROPERTY()
	UInGameHUDWidget* InGameHUD;

	/** Pointer that holds the main menu hud.
	*/
	UPROPERTY()
	UUserWidget* MainMenuHUD;

	/** Pointer that holds the main menu hud.
	*/
	UPROPERTY()
	UResetMenuWidget* ResetMenuHUD;

	/** Class that has all ingame hud elements.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UInGameHUDWidget> InGameHUDClass;

	/** Class that has Initial Main Menu.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> MainMenuHUDClass;

	/** Reset Round menu
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UResetMenuWidget> ResetHUDClass;

	/** Holds the number of kills player 1 has
	*/
	UPROPERTY(BlueprintReadOnly, Category = "GameMode")
	int32 Player1Score;

	/** Holds the number of kills player 2 has
	*/
	UPROPERTY(BlueprintReadOnly, Category = "GameMode")
	int32 Player2Score;
private:
	/** true if player 1 is dead
	*/
	bool IsPlayer1Dead;

	/** true if player 2 is dead
	*/
	bool IsPlayer2Dead;

	/** True when round ends
	*/
	bool IsRoundOver;

	/** How much time elapsed since round finished.
	*/
	float RoundEndTimeElapsed;

	/** Time elapsed since round started.
	*/
	float RoundPlayTimeElapsed;

	/** Total round time.
	*/
	float MaxRoundPlayTime;
};



