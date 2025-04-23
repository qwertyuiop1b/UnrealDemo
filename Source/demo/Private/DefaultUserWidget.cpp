// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultUserWidget.h"

#include "Components/Button.h"
#include "demo/demo.h"


void UDefaultUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UE_LOG(DEMO_APP, Warning, TEXT("This is a TEXT"));
}

void UDefaultUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	TextButton->OnClicked.AddDynamic(this, &UDefaultUserWidget::TextButtonClicked);
}

void UDefaultUserWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UDefaultUserWidget::TextButtonClicked()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("ButtonClicked"));

	OnBtnClickedDelegate.Broadcast(32);
	
}
