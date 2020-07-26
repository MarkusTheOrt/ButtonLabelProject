// Coypright Markus Ort - All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputState.h"
#include "Framework/Application/IInputProcessor.h"

DECLARE_DELEGATE_OneParam(FOnInputDeviceChangedDelegate, EInputDevices);

/**
 * 
 */
class InputDetectionProcessor : public IInputProcessor
{
private:

	EInputDevices CurrentInputDevice = EInputDevices::Keyboard;

public:

	FOnInputDeviceChangedDelegate InputDeviceChangedDelegate;
	
public:
	
	void Tick(const float DeltaTime, FSlateApplication& SlateApp, TSharedRef<ICursor> Cursor) override;

	virtual bool HandleAnalogInputEvent(FSlateApplication& SlateApp, const FAnalogInputEvent& InAnalogInputEvent) override;

	virtual bool HandleKeyDownEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent) override;

	virtual bool HandleMouseMoveEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent) override;

	virtual bool HandleMouseWheelOrGestureEvent(FSlateApplication& SlateApp, const FPointerEvent& InWheelEvent, const FPointerEvent* InGestureEvent) override;

	virtual bool HandleMouseButtonDownEvent( FSlateApplication& SlateApp, const FPointerEvent& MouseEvent) override;
		
};
