// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "demoGameModeBase.generated.h"

class UDefaultUserWidget;
/**
 * 
 */
UCLASS()
class DEMO_API AdemoGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AdemoGameModeBase();

	UDefaultUserWidget* CurrentWidget = nullptr;
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UDefaultUserWidget> DefaultUserWidgetClass;
};
