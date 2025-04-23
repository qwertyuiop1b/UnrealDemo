// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DefaultUserWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBtnClikeDelegate, int32, Num);

class UButton;
/**
 * 
 */
UCLASS()
class DEMO_API UDefaultUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
	
protected:
	virtual void NativeConstruct() override;

	virtual void NativeOnInitialized() override;

	virtual void NativeDestruct() override;

protected:

	UPROPERTY(meta=(BindWidget))
	UButton* TextButton;

	UFUNCTION()
	void TextButtonClicked();

public:
	FOnBtnClikeDelegate OnBtnClickedDelegate;
};
