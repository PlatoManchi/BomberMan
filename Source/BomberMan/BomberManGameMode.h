// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BomberManGameMode.generated.h"

UCLASS(minimalapi)
class ABomberManGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABomberManGameMode();

protected:
	// Called once when game starts
	void BeginPlay() override;

	/** Called to login new players by creating a player controller, overridable by the game.
	*
	*	Sets up basic properties of the player (name, unique id, registers with backend, etc) and should not be used to do
	*	more complicated game logic.  The player controller is not fully initialized within this function as far as networking is concerned.
	*	Save "game logic" for PostLogin which is called shortly afterward.
	*
	*	@param NewPlayer pointer to the UPlayer object that represents this player (either local or remote)
	*	@param RemoteRole the remote role this controller has
	*	@param Portal desired portal location specified by the client
	*	@param Options game options passed in by the client at login
	*	@param UniqueId platform specific unique identifier for the logging in player
	*	@param ErrorMessage [out] error message, if any, why this login will be failing
	*
	*	If login is successful, returns a new PlayerController to associate with this player. Login fails if ErrorMessage string is set.
	*
	*	@return a new player controller for the logged in player, NULL if login failed for any reason
	*/
	virtual APlayerController* Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
};



