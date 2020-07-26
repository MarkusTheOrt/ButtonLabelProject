// Coypright Markus Ort - All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Modules/ModuleManager.h"
#include "ButtonLabelProject.generated.h"

DECLARE_MULTICAST_DELEGATE(FChangeButtonLabelsDelegate);

USTRUCT()
struct FKeyToTexture : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FKey Key;

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UTexture2D> Texture;
};

class InputDetectionProcessor;
enum class EInputDevices;

class FButtonLabelGameModule : public IModuleInterface
{
protected:
	
	TSharedPtr<InputDetectionProcessor> InputProcessor;

	EInputDevices CurrentInputDevice;
	
public:

	FChangeButtonLabelsDelegate InputDeviceChangedDelegate;

public:
	
	virtual void StartupModule() override;

	virtual void ShutdownModule() override;

	virtual bool IsGameModule() const override
	{
		return true;
	}

	void OnInputDeviceChanged(EInputDevices NewInputDevice);
	
	TSoftObjectPtr<UTexture2D> GetTextureForKey(FName InputName);
	
};
