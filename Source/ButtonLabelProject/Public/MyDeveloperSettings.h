// Coypright Markus Ort - All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "MyDeveloperSettings.generated.h"

class UDataTable;

/**
 * 
 */
UCLASS(Config=Engine)
class BUTTONLABELPROJECT_API UMyDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, Config)	
	TSoftObjectPtr<UDataTable> KeyMapPtr;


	virtual FName GetContainerName() const override
	{
		return "Project";
	}
	virtual FName GetCategoryName() const override
	{
		return "Game";
	}
	virtual FName GetSectionName() const override
	{
		return "Button Label Settings";
	}
};
