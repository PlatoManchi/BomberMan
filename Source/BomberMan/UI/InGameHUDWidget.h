// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameHUDWidget.generated.h"

class ABomberManCharacter;
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
	void SetPlayer1(ABomberManCharacter* Player);
	
	/** Sets the player 2's player state
	*	@param PlayerState Player state of player 1.
	*/
	void SetPlayer2(ABomberManCharacter* Player);

	/** When player 1 pick up Remote bomb pick up.
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "InGameHUD")
	void Player1RemoteBomb(float MaxTime);

	/** When player 2 pick up Remote bomb pick up.
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "InGameHUD")
	void Player2RemoteBomb(float MaxTime);

	/** Reset the HUD.
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "InGameHUD")
	void Reset();

	/** Set the timer in UI to show re
	*/
	UFUNCTION(BlueprintImplementableEvent, Category = "InGameHUD")
	void SetTimer(float RemainingTime);
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

	/** When player 1 pick up Remote bomb pick up.
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "InGameHUD")
	void Player1RemoteBombHide();

	/** When player 2 pick up Remote bomb pick up.
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "InGameHUD")
	void Player2RemoteBombHide();

	/** Caching the Player 1 player state
	*/
	UPROPERTY(BlueprintReadOnly, Category = "InGameHUD")
	ABomberManPlayerState* Player1State;

	/** Caching the Player 2 player state
	*/
	UPROPERTY(BlueprintReadOnly, Category = "InGameHUD")
	ABomberManPlayerState* Player2State;
	
private:
	/** Cache previous values so as to know when value changes
	*/
	int32 PrevPlayer1MaxBombs, PrevPlayer1CurrentBombs;
	int32 PrevPlayer2MaxBombs, PrevPlayer2CurrentBombs;

	/** Remote bomb time elapsed
	*/
	bool IsPlayer1RemoteBomb;
	bool IsPlayer2RemoteBomb;


	UPROPERTY(BlueprintReadOnly, Category = "InGameHUD", meta = (AllowPrivateAccess = "true"))
	float Player1RemoteBombTimeElapsed;

	UPROPERTY(BlueprintReadOnly, Category = "InGameHUD", meta = (AllowPrivateAccess = "true"))
	float Player1RemoteBombMaxTime;

	UPROPERTY(BlueprintReadOnly, Category = "InGameHUD", meta = (AllowPrivateAccess = "true"))
	float Player2RemoteBombTimeElapsed;

	UPROPERTY(BlueprintReadOnly, Category = "InGameHUD", meta = (AllowPrivateAccess = "true"))
	float Player2RemoteBombMaxTime;
};
