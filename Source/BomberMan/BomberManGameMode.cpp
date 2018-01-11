// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "BomberManGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

ABomberManGameMode::ABomberManGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Characters/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ABomberManGameMode::BeginPlay()
{
	// Creating another player so that there are two players
	UGameplayStatics::CreatePlayer(GetWorld(), 1);
}
