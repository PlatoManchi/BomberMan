// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "BomberManGameMode.h"
#include "Camera/BomberManCamera.h"
#include "Characters/BomberManPlayerState.h"

// Engine includes
#include "EngineUtils.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"



ABomberManGameMode::ABomberManGameMode()
{
	// Set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Characters/BP_ThirdPersonCharacter"));
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
}
