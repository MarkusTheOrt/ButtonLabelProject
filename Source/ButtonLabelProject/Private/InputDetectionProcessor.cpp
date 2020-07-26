// Coypright Markus Ort - All Rights Reserved.


#include "InputDetectionProcessor.h"

void InputDetectionProcessor::Tick(const float DeltaTime, FSlateApplication& SlateApp, TSharedRef<ICursor> Cursor)
{
}

bool InputDetectionProcessor::HandleAnalogInputEvent(FSlateApplication& SlateApp,
	const FAnalogInputEvent& InAnalogInputEvent)
{
	if(InAnalogInputEvent.GetKey().IsGamepadKey() && CurrentInputDevice != EInputDevices::Gamepad
		&& InAnalogInputEvent.GetAnalogValue() > 0.15f)
	{
		CurrentInputDevice = EInputDevices::Gamepad;
		InputDeviceChangedDelegate.ExecuteIfBound(CurrentInputDevice);
	}	
	return false;
}

bool InputDetectionProcessor::HandleKeyDownEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent)
{
	if(InKeyEvent.GetKey().IsGamepadKey() && CurrentInputDevice != EInputDevices::Gamepad)
	{
		CurrentInputDevice = EInputDevices::Gamepad;
		InputDeviceChangedDelegate.ExecuteIfBound(CurrentInputDevice);
		return false;
	}
	if(!InKeyEvent.GetKey().IsGamepadKey() && CurrentInputDevice != EInputDevices::Keyboard)
	{
		CurrentInputDevice = EInputDevices::Keyboard;
		InputDeviceChangedDelegate.ExecuteIfBound(CurrentInputDevice);
		return false;
	}
	return false;
}

bool InputDetectionProcessor::HandleMouseMoveEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent)
{
	if(CurrentInputDevice != EInputDevices::Keyboard && MouseEvent.GetCursorDelta().Size() > 2.f)
	{
		CurrentInputDevice = EInputDevices::Keyboard;
		InputDeviceChangedDelegate.ExecuteIfBound(CurrentInputDevice);
	}
	return false;
}

bool InputDetectionProcessor::HandleMouseWheelOrGestureEvent(FSlateApplication& SlateApp,
	const FPointerEvent& InWheelEvent, const FPointerEvent* InGestureEvent)
{
	if(CurrentInputDevice != EInputDevices::Keyboard)
	{
		CurrentInputDevice = EInputDevices::Keyboard;
		InputDeviceChangedDelegate.ExecuteIfBound(CurrentInputDevice);
	}
	return false;
}

bool InputDetectionProcessor::HandleMouseButtonDownEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent)
{
	if(CurrentInputDevice != EInputDevices::Keyboard)
	{
		CurrentInputDevice = EInputDevices::Keyboard;
		InputDeviceChangedDelegate.ExecuteIfBound(CurrentInputDevice);
	}
	return false;
}
