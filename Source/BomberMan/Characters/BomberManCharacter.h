// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BomberManCharacter.generated.h"

// Forward decelerations
class ABomberManController;
class ABomb;

UCLASS(config=Game)
class ABomberManCharacter : public ACharacter
{
	GENERATED_BODY()

	// Giving full access of character to controller.
	friend class ABomberManController;

public:
	/** Default constructor
	*/
	ABomberManCharacter();

protected:
	/** Called when this Pawn is possessed.
	*	@param NewController The controller possessing this pawn
	*/
	virtual void PossessedBy(AController* NewController) override;

	/** Called for forwards/backward input 
	*	@param Value The value representing input in vertical axis
	*/
	void MoveForward(float Value);

	/** Called for side to side input 
	*	@param Value The value representing input in horizontal axis
	*/
	void MoveRight(float Value);

	/** If able to, place the bomb at character's location.
	*/
	void PlaceBomb();

	UFUNCTION(BlueprintImplementableEvent, Category = "BomberManCharacter")
	void SetPlayerID(int32 id);

private:
	/** Type of bomb this character can place.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BomberManCharacter|Weapon", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ABomb> BombTypeClass;
};

