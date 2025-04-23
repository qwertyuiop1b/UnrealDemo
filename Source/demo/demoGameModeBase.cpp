// Copyright Epic Games, Inc. All Rights Reserved.


#include "demoGameModeBase.h"

#include "DefaultUserWidget.h"
#include "DemoPawn.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

class UCameraComponent;

AdemoGameModeBase::AdemoGameModeBase()
{
	DefaultPawnClass = ADemoPawn::StaticClass();
}

void AdemoGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Begin Play"));

	if (DefaultUserWidgetClass != nullptr)
	{
		CurrentWidget= CreateWidget<UDefaultUserWidget>(GetWorld(), DefaultUserWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}
