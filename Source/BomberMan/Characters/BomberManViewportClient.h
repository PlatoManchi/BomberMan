// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameViewportClient.h"
#include "BomberManViewportClient.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMAN_API UBomberManViewportClient : public UGameViewportClient
{
	GENERATED_BODY()
	
protected:
	/**	Check a key event received by the viewport. If the viewport client uses the event, it should return true to consume it.
	*	@param Viewport The viewport which the key event is from.
	*	@param ControllerId The controller which the key event is from.
	*	@param Key The name of the key which an event occurred for.
	*	@param Event The type of event which occurred.
	*	@param AmountDepressed For analog keys, the depression percent.
	*	@param bGamepad Input came from gamepad (ie xbox controller)
	*	@return True to consume the key event, false to pass it on.
	*/
	virtual bool InputKey(FViewport* Viewport, int32 ControllerId, FKey Key, EInputEvent EventType, float AmountDepressed = 1.f, bool bGamepad = false) override;

	/** Check an axis movement received by the viewport. If the viewport client uses the movement, it should return true to consume it.
	*	@param Viewport The viewport which the axis movement is from.
	*	@param ControllerId The controller which the axis movement is from.
	*	@param Key The name of the axis which moved.
	*	@param Delta The axis movement delta.
	*	@param DeltaTime The time since the last axis update.
	*	@param NumSamples The number of device samples that contributed to this Delta, useful for things like smoothing
	*	@param bGamepad Input came from gamepad (ie xbox controller)
	*	@return True to consume the axis movement, false to pass it on.
	*/
	virtual bool InputAxis(FViewport* Viewport, int32 ControllerId, FKey Key, float Delta, float DeltaTime, int32 NumSamples = 1, bool bGamepad = false) override;
	
};
