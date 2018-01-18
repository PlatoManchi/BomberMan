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
	
};
