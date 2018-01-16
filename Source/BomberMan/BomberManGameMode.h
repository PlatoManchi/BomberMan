// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BomberManGameMode.generated.h"

class UInGameHUDWidget;

UCLASS(minimalapi)
class ABomberManGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABomberManGameMode();

protected:
	// Called once when game starts
	void BeginPlay() override;

	/** Called after a successful login.  This is the first place it is safe to call replicated functions on the PlayerController.
	*	@param NewPlayer A new player controller for the logged in player, NULL if login failed for any reason
	*/
	virtual void PostLogin(APlayerController* NewPlayer) override;

	/** Pointer that holds the ingame hud widget
	*/
	UInGameHUDWidget* InGameHUD;

	/** Class that has all ingame hud elements.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UInGameHUDWidget> InGameHUDClass;


};



