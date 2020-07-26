// Coypright Markus Ort - All Rights Reserved.

#include "ButtonLabelProject.h"
#include "Modules/ModuleManager.h"
#include "InputDetectionProcessor.h"
#include "MyDeveloperSettings.h"
#include "GameFramework/InputSettings.h"

IMPLEMENT_PRIMARY_GAME_MODULE(FButtonLabelGameModule, ButtonLabelProject, "ButtonLabelProject");


void FButtonLabelGameModule::StartupModule()
{
	CurrentInputDevice = EInputDevices::Keyboard;
	const auto DevSettings = GetDefault<UMyDeveloperSettings>();
	DevSettings->KeyMapPtr.LoadSynchronous()->AddToRoot();
	if (FSlateApplication::IsInitialized())
	{
		InputProcessor = MakeShared<InputDetectionProcessor>();
		auto& SlateApp = FSlateApplication::Get();
		SlateApp.RegisterInputPreProcessor(InputProcessor);
		InputProcessor->InputDeviceChangedDelegate.BindRaw(this, &FButtonLabelGameModule::OnInputDeviceChanged);
	}
	
}

void FButtonLabelGameModule::ShutdownModule()
{
	if(FSlateApplication::IsInitialized() && InputProcessor.IsValid())
	{
		auto& SlateApp = FSlateApplication::Get();
		SlateApp.UnregisterInputPreProcessor(InputProcessor);
		InputProcessor.Reset();
	}
}

void FButtonLabelGameModule::OnInputDeviceChanged(EInputDevices NewInputDevice)
{
	CurrentInputDevice = NewInputDevice;
	InputDeviceChangedDelegate.Broadcast();
}

TSoftObjectPtr<UTexture2D> FButtonLabelGameModule::GetTextureForKey(FName InputName)
{

	const auto DevSettings = GetDefault<UMyDeveloperSettings>();
	const auto InputSettings = GetDefault<UInputSettings>();
	UDataTable* KeyMap = DevSettings->KeyMapPtr.Get();
	if(KeyMap->GetRowStruct() != FKeyToTexture::StaticStruct()) return nullptr;
	TArray<FInputActionKeyMapping> FoundMappings;
	InputSettings->GetActionMappingByName(InputName, FoundMappings);

	for(const auto& FoundMapping : FoundMappings)
	{
		if(CurrentInputDevice == EInputDevices::Gamepad && !FoundMapping.Key.IsGamepadKey()) continue;
		FString Context;
		FKeyToTexture* Data = KeyMap->FindRow<FKeyToTexture>(FoundMapping.Key.GetFName(), Context, true);
		if(Data && Context.IsEmpty())
			return Data->Texture;
	}

	return nullptr;
	
}
