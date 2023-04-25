// Fill out your copyright notice in the Description page of Project Settings.


#include "../Character/MyPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "../MyGameModeBase.h"
#include "../HexGrid/HexTile.h"

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetShowMouseCursor(true);

	GameMode = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (!GameMode)
	{
		UE_LOG(LogTemp, Error, TEXT("GameMode is not valid!"));
	}

	UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (IMC_Default && SubSystem)
	{
		SubSystem->AddMappingContext(IMC_Default, 0);
	}

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	if (EnhancedInputComponent->IsValidLowLevelFast())
	{
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *EnhancedInputComponent->GetName());
		if (IA_LeftClick)
		{
			EnhancedInputComponent->BindAction(IA_LeftClick, ETriggerEvent::Started, this, &AMyPlayerController::LeftClickPressed);
		}
	}
}

void AMyPlayerController::LeftClickPressed()
{
	//UE_LOG(LogTemp, Warning, TEXT("LeftClickPressed Called"));

	FVector WorldLocation, WorldDirection;

	if (DeprojectMousePositionToWorld(WorldLocation, WorldDirection))
	{
		FVector EndPoint = WorldLocation + (WorldDirection * LineTraceDistance);
		//UE_LOG(LogTemp, Warning, TEXT("Start : %s, End : %s"), *WorldLocation.ToString(), *EndPoint.ToString());
		FHitResult HitResult;
		FCollisionObjectQueryParams ObjectQueryParams;
		ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);

		DrawDebugLine(GetWorld(), WorldLocation, EndPoint, FColor::Green, true, 300.0f);

		if (GetWorld()->LineTraceSingleByObjectType(HitResult, WorldLocation, EndPoint, ObjectQueryParams))
		{
			//UE_LOG(LogTemp, Warning, TEXT("Hitted : %s"), *HitResult.GetActor()->GetName());
			if (AHexTile* HexTile = Cast<AHexTile>(HitResult.GetActor()))
			{

			}
		}
	}
}