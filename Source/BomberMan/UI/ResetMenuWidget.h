// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ResetMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMAN_API UResetMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
	
public:
	/** Update the text for showing score
	*/
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateScore();
	
	/** Set the winning team for this round.
	*	@param PlayerID Id of player that won the game. If draw then -1
	*/
	UFUNCTION(BlueprintImplementableEvent)
	void SetWinningTeam(int32 PlayerID);
};
