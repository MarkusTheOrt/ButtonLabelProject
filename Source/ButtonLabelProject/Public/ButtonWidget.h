// Coypright Markus Ort - All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "Engine/StreamableManager.h"

#include "ButtonWidget.generated.h"

DECLARE_DYNAMIC_DELEGATE_RetVal(FName, FGetName);


/**
 * 
 */
UCLASS()
class BUTTONLABELPROJECT_API UButtonWidget : public UWidget
{
	GENERATED_BODY()

public:

	UButtonWidget();

	UPROPERTY()
	FSlateBrush Brush;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Appearance)
	FName InputBinding;

	UPROPERTY()
	FGetName InputBindingDelegate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Appearance, meta = (sRGB = "true"))
	FLinearColor ColorAndOpacity;

	UPROPERTY()
	FGetLinearColor ColorAndOpacityDelegate;

	UPROPERTY(EditAnywhere, Category = Localization)
	bool bFlipForRightToLeftFlowDirection;

	UPROPERTY(EditAnywhere, Category = Events, meta = (IsBindableEvent = "true"))
	FOnPointerEvent OnMouseButtonDown;

	FDelegateHandle InputChangedDelegate;

protected:

	TSharedPtr<SImage> ImageWidget;

	TSharedPtr<FStreamableHandle> StreamingHandle;

	FSoftObjectPath StreamingObjectPath;

	PROPERTY_BINDING_IMPLEMENTATION(FName, InputBinding);
	PROPERTY_BINDING_IMPLEMENTATION(FSlateColor, ColorAndOpacity);
	
public:

	UFUNCTION(BlueprintCallable, Category = Appearance)
    void SetInputBinding(FName InBinding);
	
	UFUNCTION(BlueprintCallable, Category = Appearance)
	void SetColorAndOpacity(FLinearColor InColorAndOpacity);

	UFUNCTION(BlueprintCallable, Category = Appearance)
	void SetOpacity(float InOpacity);

	void OnInputTypeChanged();

	void SetBrushFromTexture(UTexture2D* Texture);

	void SetBrushFromSoftTexture(TSoftObjectPtr<UTexture2D> SoftTexture);

	void RequestAsyncLoad(TSoftObjectPtr<UObject> SoftObject, TFunction<void()>&& Callback);

	virtual void RequestAsyncLoad(TSoftObjectPtr<UObject> SoftObject, FStreamableDelegate DelegateToCall);

	virtual void CancelImageStreaming();
	
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	
	virtual void SynchronizeProperties() override;

protected:

	FReply HandleMouseButtonDown(const FGeometry& Geometry, const FPointerEvent& MouseEvent);
	
#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override;
#endif	
protected:
	
	virtual TSharedRef<SWidget> RebuildWidget() override;
	
#if WITH_ACCESSIBILITY
	virtual TSharedPtr<SWidget> GetAccessibleWidget() const override;
#endif
	
};
