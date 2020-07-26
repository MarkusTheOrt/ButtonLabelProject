// Coypright Markus Ort - All Rights Reserved.


#include "ButtonWidget.h"

#include "ButtonLabelProject/ButtonLabelProject.h"
#include "Engine/AssetManager.h"
#include "Widgets/Images/SImage.h"

#define LOCTEXT_NAMESPACE "ButtonWidget"

UButtonWidget::UButtonWidget()
	: InputBinding(NAME_None)
	, ColorAndOpacity(FLinearColor::White)
{
}

void UButtonWidget::SetInputBinding(FName InBinding)
{
	InputBinding = InBinding;
	if(ImageWidget.IsValid())
	{
		OnInputTypeChanged();
	}
}

void UButtonWidget::SetColorAndOpacity(FLinearColor InColorAndOpacity)
{
	ColorAndOpacity = InColorAndOpacity;
	if(ImageWidget.IsValid())
	{
		ImageWidget->SetColorAndOpacity(ColorAndOpacity);
	}
}

void UButtonWidget::SetOpacity(float InOpacity)
{
	ColorAndOpacity.A = InOpacity;
	if(ImageWidget.IsValid())
	{
		ImageWidget->SetColorAndOpacity(ColorAndOpacity);
	}
}

void UButtonWidget::OnInputTypeChanged()
{
	Brush.SetResourceObject(nullptr);
	if(ImageWidget.IsValid())
	{
		auto& GameModule = FModuleManager::GetModuleChecked<FButtonLabelGameModule>("ButtonLabelProject");
		auto Texture = GameModule.GetTextureForKey(InputBinding);
		if(!Texture.IsNull())
			SetBrushFromSoftTexture(GameModule.GetTextureForKey(InputBinding));
	}
}

void UButtonWidget::SetBrushFromTexture(UTexture2D* Texture)
{
	if(Brush.GetResourceObject() != Texture)
	{
		Brush.SetResourceObject(Texture);

		if(Texture)
		{
			Texture->bForceMiplevelsToBeResident = true;
			Texture->bIgnoreStreamingMipBias = true;
			Brush.ImageSize.X = Texture->GetSizeX();
			Brush.ImageSize.Y = Texture->GetSizeY();
		}

		if(ImageWidget.IsValid())
		{
			ImageWidget->SetImage(&Brush);
		}
		
	}
}

void UButtonWidget::SetBrushFromSoftTexture(TSoftObjectPtr<UTexture2D> SoftTexture)
{
	TWeakObjectPtr<UButtonWidget> WeakThis(this);

	RequestAsyncLoad(SoftTexture, [WeakThis, SoftTexture]()
	{
		if(UButtonWidget* StrongThis = WeakThis.Get())
		{
			ensureMsgf(SoftTexture.Get(), TEXT("Failed to load %s"), *SoftTexture.ToSoftObjectPath().ToString());
			StrongThis->SetBrushFromTexture(SoftTexture.Get());
		}
	});
}

void UButtonWidget::RequestAsyncLoad(TSoftObjectPtr<UObject> SoftObject, TFunction<void()>&& Callback)
{
	RequestAsyncLoad(SoftObject, FStreamableDelegate::CreateLambda(MoveTemp(Callback)));
}

void UButtonWidget::RequestAsyncLoad(TSoftObjectPtr<UObject> SoftObject, FStreamableDelegate DelegateToCall)
{
	CancelImageStreaming();

	if(UObject* StrongObject = SoftObject.Get())
	{
		DelegateToCall.ExecuteIfBound();
		return;
	}

	TWeakObjectPtr<UButtonWidget> WeakThis(this);
	StreamingObjectPath = SoftObject.ToSoftObjectPath();
	StreamingHandle = UAssetManager::GetStreamableManager().RequestAsyncLoad(
		StreamingObjectPath,
		[WeakThis, DelegateToCall, SoftObject]()
		{
			if(UButtonWidget* StrongThis = WeakThis.Get())
			{
				if(StrongThis->StreamingObjectPath != SoftObject.ToSoftObjectPath())
				{
					return;
				}

				DelegateToCall.ExecuteIfBound();
			}
		}, FStreamableManager::AsyncLoadHighPriority);

	
}

void UButtonWidget::CancelImageStreaming()
{
	if(StreamingHandle.IsValid())
	{
		StreamingHandle->CancelHandle();
		StreamingHandle.Reset();
	}
	StreamingObjectPath.Reset();
}

void UButtonWidget::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	ImageWidget.Reset();
}

void UButtonWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	if(!InputChangedDelegate.IsValid())
	{
		auto& GameModule = FModuleManager::GetModuleChecked<FButtonLabelGameModule>("ButtonLabelProject");
		InputChangedDelegate = GameModule.InputDeviceChangedDelegate.AddUObject(
			this,
			&UButtonWidget::OnInputTypeChanged
		);
	}

	TAttribute<FName> InputBindingBinding = PROPERTY_BINDING(FName, InputBinding);
	TAttribute<FSlateColor> ColorAndOpacityBinding = PROPERTY_BINDING(FSlateColor, ColorAndOpacity);

	if(ImageWidget.IsValid())
	{
		this->SetInputBinding(InputBinding);
		ImageWidget->SetImage(&Brush);
		ImageWidget->SetColorAndOpacity(ColorAndOpacityBinding);
		ImageWidget->SetOnMouseButtonDown(BIND_UOBJECT_DELEGATE(FPointerEventHandler, HandleMouseButtonDown));
	}
	
}

FReply UButtonWidget::HandleMouseButtonDown(const FGeometry& Geometry, const FPointerEvent& MouseEvent)
{
	if(OnMouseButtonDown.IsBound())
	{
		return OnMouseButtonDown.Execute(Geometry, MouseEvent).NativeReply;
	}
	return FReply::Unhandled();
}

#if WITH_EDITOR
const FText UButtonWidget::GetPaletteCategory()
{
	return LOCTEXT("Common", "Common");
}
#endif

TSharedRef<SWidget> UButtonWidget::RebuildWidget()
{
	ImageWidget = SNew(SImage)
					.FlipForRightToLeftFlowDirection(bFlipForRightToLeftFlowDirection);
	return ImageWidget.ToSharedRef();
}

#if WITH_ACCESSIBILITY
TSharedPtr<SWidget> UButtonWidget::GetAccessibleWidget() const
{
	return ImageWidget;
}
#endif

#undef LOCTEXT_NAMESPACE