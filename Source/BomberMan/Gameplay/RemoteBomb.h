// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/Bomb.h"
#include "RemoteBomb.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMAN_API ARemoteBomb : public ABomb
{
	GENERATED_BODY()
	
protected:
	/** Ability to override and change the behavior
	*/
	virtual void SetOwningCharacter_Implementation(ABomberManCharacter* NewOwningCharacter) override;
	
};
