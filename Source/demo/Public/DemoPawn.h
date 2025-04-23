// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "DemoPawn.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class DEMO_API ADemoPawn : public APawn
{
	GENERATED_BODY()

public:
	ADemoPawn();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Orbit")
	float RotationSpeed = 50.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Orbit")
	float ZoomSpeed = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Orbit")
	float MinDistance = 200.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Orbit")
	float MaxDistance =  5000.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Orbit")
	float PanSpeed = 10.f;
	
public:	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void OnDefaultWidgetBtnClicked(int32 Num);

private:
	
	void OnMouseX(float Value);
	void OnMouseY(float Value);
	void OnMouseWheel(float Value);
	void OnPanX(float Value);
	void OnPanY(float Value);

	void OnRotateOrbitStart();
	void OnRotateOrbitEnd();
	void OnPanOrbitStart();
	void OnPanOrbitEnd();

	bool bIsRotating;
	bool bIsPanning;
	
};
