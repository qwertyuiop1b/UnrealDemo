// Fill out your copyright notice in the Description page of Project Settings.

#include "DemoPawn.h"

#include "DefaultUserWidget.h"
#include "Camera/CameraComponent.h"
#include "demo/demoGameModeBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ADemoPawn::ADemoPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DemoMesh"));
	StaticMesh->SetupAttachment(RootComponent);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArm->TargetArmLength = 500.0f;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->CameraRotationLagSpeed = 10.f;
	SpringArm->SetupAttachment(StaticMesh);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	Camera->SetupAttachment(SpringArm);


	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
}


void ADemoPawn::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	
	if (PC != nullptr)
	{
		const auto Actor = PC->GetViewTarget();
		if (Actor != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Location: %s"), *Actor->GetActorLocation().ToString());
		}
		PC->SetViewTarget(this);
	}

	const auto GameMode = Cast<AdemoGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (GameMode != nullptr)
	{
		GameMode->CurrentWidget->OnBtnClickedDelegate.AddUniqueDynamic(this, &ADemoPawn::OnDefaultWidgetBtnClicked);
	}
	
}


void ADemoPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ADemoPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MouseX", this, &ADemoPawn::OnMouseX);
	PlayerInputComponent->BindAxis("MouseY", this, &ADemoPawn::OnMouseY);
	PlayerInputComponent->BindAction("RotateOrbit", IE_Pressed, this, &ADemoPawn::OnRotateOrbitStart);
	PlayerInputComponent->BindAction("RotateOrbit", IE_Released, this, &ADemoPawn::OnRotateOrbitEnd);

	PlayerInputComponent->BindAxis("MouseWheel", this, &ADemoPawn::OnMouseWheel);

	PlayerInputComponent->BindAction("PanOrbit", IE_Pressed, this, &ADemoPawn::OnPanOrbitStart);
	PlayerInputComponent->BindAction("PanOrbit", IE_Released, this, &ADemoPawn::OnPanOrbitEnd);

	PlayerInputComponent->BindAxis("PanX", this, &ADemoPawn::OnPanX);
	PlayerInputComponent->BindAxis("PanY", this, &ADemoPawn::OnPanY);
}

void ADemoPawn::OnDefaultWidgetBtnClicked(int32 Num)
{
	const FString DebugString = FString::Printf(TEXT("DefaultWidgetBtnClicked: %d"), Num);
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, DebugString);
}

void ADemoPawn::OnMouseX(float Value)
{
	if (bIsRotating && FMath::Abs(Value) > 0.f)
	{
		FRotator NewRotation = SpringArm->GetRelativeRotation();
		NewRotation.Yaw += Value * RotationSpeed * GetWorld()->GetDeltaSeconds();
		SpringArm->SetRelativeRotation(NewRotation);
	}
	
}

void ADemoPawn::OnMouseY(float Value)
{
	if (bIsRotating && FMath::Abs(Value) > 0.f)
	{
		FRotator NewRotation = SpringArm->GetRelativeRotation();
		NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + Value * RotationSpeed * GetWorld()->GetDeltaSeconds(), -89.f, 89.f);
		SpringArm->SetRelativeRotation(NewRotation);
	}
}

void ADemoPawn::OnMouseWheel(float Value)
{
	if (FMath::Abs(Value) > 0.f)
	{
		float NewLength = SpringArm->TargetArmLength - Value * ZoomSpeed;
		NewLength = FMath::Clamp(NewLength, MinDistance, MaxDistance);
		SpringArm->TargetArmLength = NewLength;
	}
}

void ADemoPawn::OnPanX(float Value)
{
	if (bIsPanning && FMath::Abs(Value) > 0.f)
	{
		UE_LOG(LogTemp, Warning, TEXT("PanX: %f"), Value);
		FVector Right = Camera->GetRightVector();
		AddActorWorldOffset(Right * Value * PanSpeed);
	}
}

void ADemoPawn::OnPanY(float Value)
{
	if (bIsPanning && FMath::Abs(Value) > 0.f)
	{
		FVector Forward = Camera->GetForwardVector();
		Forward.Z = 0;
		Forward.Normalize();
		AddActorWorldOffset(Forward * Value * PanSpeed);
	}
}

void ADemoPawn::OnRotateOrbitStart()
{
	bIsRotating = true;
}

void ADemoPawn::OnRotateOrbitEnd()
{
	bIsRotating = false;
}

void ADemoPawn::OnPanOrbitStart()
{
	bIsPanning = true;
}

void ADemoPawn::OnPanOrbitEnd()
{
	bIsPanning = false;
}

