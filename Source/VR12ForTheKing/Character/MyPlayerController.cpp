// Fill out your copyright notice in the Description page of Project Settings.


#include "../Character/MyPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "../MyGameModeBase.h"

#include "../HexGrid/HexTile.h"
#include "../Character/MyCharacter.h"
#include "../Component/MoveManagerComponent.h"

#include "../Event/EventActor.h"

AMyPlayerController::AMyPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

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
	else
	{
		UE_LOG(LogTemp, Error, TEXT("SubSystem or IMC is not valid!"));
	}

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	if (EnhancedInputComponent)
	{
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *EnhancedInputComponent->GetName());
		if (IA_LeftClick)
		{
			EnhancedInputComponent->BindAction(IA_LeftClick, ETriggerEvent::Started, this, &AMyPlayerController::LeftClickPressed);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("IA_LeftClick is not valid!"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("EnhancedInputComponent is not valid!"));
	}
}

void AMyPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckEndTile();
}

const FText AMyPlayerController::GetPlayerName() const
{
	return PlayerName;
}

void AMyPlayerController::LeftClickPressed()
{
	// Multi 로 바꾸면 꼭 손봐야함
	GameMode->LeftClick(this);
}

void AMyPlayerController::CheckEndTile()
{
	AActor* HitActor = CheckTile();

	if (EventActor && HitActor != EventActor)
	{
		GameMode->HideEventInfoWidget();
		EventActor = NULL;
	}
	if (HitActor == NULL) return;

	if (!GameMode->GetIsMoved() && GameMode->GetCurrentPlayer() == this)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 60, FColor::Yellow, FString::Printf(TEXT("CheckEndTile Called")));

		AHexTile* HexTile = Cast<AHexTile>(HitActor);
		if (HexTile)
		{
			GameMode->SetEndTile(HexTile);
		}
	}

	AEventActor* NewEventActor = Cast<AEventActor>(HitActor);
	if (NewEventActor && (EventActor == NULL || EventActor != NewEventActor))
	{
		EventActor = NewEventActor;
		FVector2D ScreenLocation;
		ProjectWorldLocationToScreen(EventActor->GetActorLocation(), ScreenLocation);
		UE_LOG(LogTemp, Warning, TEXT("Event Actor : %s's Location : %s"), *EventActor->GetName(), *ScreenLocation.ToString());
		GameMode->InitAndShowEventInfoWidget(EventActor, ScreenLocation);
	}
}

AActor* AMyPlayerController::CheckTile()
{
	FVector WorldLocation, WorldDirection;

	if (DeprojectMousePositionToWorld(WorldLocation, WorldDirection))
	{
		FVector EndPoint = WorldLocation + (WorldDirection * LineTraceDistance);
		//UE_LOG(LogTemp, Warning, TEXT("Start : %s, End : %s"), *WorldLocation.ToString(), *EndPoint.ToString());
		FHitResult HitResult;
		FCollisionObjectQueryParams ObjectQueryParams;
		ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
		ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

		//DrawDebugLine(GetWorld(), WorldLocation, EndPoint, FColor::Green, true, 300.0f);

		if (GetWorld()->LineTraceSingleByObjectType(HitResult, WorldLocation, EndPoint, ObjectQueryParams))
		{
			return HitResult.GetActor();
		}
	}

	return NULL;
}
