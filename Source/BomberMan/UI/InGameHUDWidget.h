// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameHUDWidget.generated.h"

class ABomberManPlayerState;

/**
 * 
 */
UCLASS()
class BOMBERMAN_API UInGameHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	/** Sets the player 1's player state
	*	@param PlayerState Player state of player 1.
	*/
	void SetPlayer1State(ABomberManPlayerState* PlayerState);
	
	/** Sets the player 2's player state
	*	@param PlayerState Player state of player 1.
	*/
	void SetPlayer2State(ABomberManPlayerState* PlayerState);

protected:
	/** Called every frame
	*/
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	/** Set the player 1 maximum bombs available
	*/
	UFUNCTION(BlueprintImplementableEvent, Category = "InGameHUD")
	void SetPlayer1MaxBombs(int32 MaxBombs);

	/** Set the player 1 current bombs available
	*/
	UFUNCTION(BlueprintImplementableEvent, Category = "InGameHUD")
	void SetPlayer1CurrentBombs(int32 CurrentBombs);

	/** Set the player 2 maximum bombs available
	*/
	UFUNCTION(BlueprintImplementableEvent, Category = "InGameHUD")
	void SetPlayer2MaxBombs(int32 MaxBombs);

	/** Set the player 2 current bombs available
	*/
	UFUNCTION(BlueprintImplementableEvent, Category = "InGameHUD")
	void SetPlayer2CurrentBombs(int32 CurrentBombs);

	/** Caching the Player 1 player state
	*/
	UPROPERTY(BlueprintReadOnly, Category = "InGameHUD")
	ABomberManPlayerState* Player1State;

	/** Caching the Player 2 player state
	*/
	UPROPERTY(BlueprintReadOnly, Category = "InGameHUD")
	ABomberManPlayerState* Player2State;
	
private:
	int32 PrevPlayer1MaxBombs, PrevPlayer1CurrentBombs;
	int32 PrevPlayer2MaxBombs, PrevPlayer2CurrentBombs;
};
