// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BomberManCharacter.generated.h"

// Forward decelerations
class ABomberManController;

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

	/** Returns CameraBoom subobject 
	*/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Returns FollowCamera subobject 
	*/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

protected:
	/** Called for forwards/backward input 
	*	@param Value The value representing input in vertical axis
	*/
	void MoveForward(float Value);

	/** Called for side to side input 
	*	@param Value The value representing input in horizontal axis
	*/
	void MoveRight(float Value);

private:

	/** Camera boom positioning the camera behind the character 
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera 
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
};

