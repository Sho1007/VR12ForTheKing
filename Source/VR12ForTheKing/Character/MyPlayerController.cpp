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
#include "../Component/BattleManagerComponent.h"
#include "../Component/BattleComponent.h"
#include "../Event/EventActor.h"
#include "../Widget/ActionWidget.h"

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
		checkf(IA_LeftClick != nullptr, TEXT("IA_LeftClick is not valid!"));
		EnhancedInputComponent->BindAction(IA_LeftClick, ETriggerEvent::Started, this, &AMyPlayerController::LeftClickPressed);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("EnhancedInputComponent is not valid!"));
	}
}

void AMyPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckFocusActor();
}

const FText AMyPlayerController::GetPlayerName() const
{
	return PlayerName;
}

void AMyPlayerController::AddPlayerCharacter(AMyCharacter* NewPlayerCharacter)
{
	checkf(NewPlayerCharacter != nullptr, TEXT("NewPlayerCharacter is nullptr"));
	PlayerCharacterArray.Add(NewPlayerCharacter);
}

void AMyPlayerController::MoveToNextCharacterIndex()
{
	CurrentCharacterIndex = (CurrentCharacterIndex + 1) % PlayerCharacterArray.Num();
}

AMyCharacter* AMyPlayerController::GetPlayerCharacter()
{
	return PlayerCharacterArray[CurrentCharacterIndex];
}

void AMyPlayerController::LeftClickPressed()
{
	// Multi 로 바꾸면 꼭 손봐야함
	UBattleManagerComponent* BattleManagerComponent = Cast<UBattleManagerComponent>(GameMode->GetComponentByClass(UBattleManagerComponent::StaticClass()));
	checkf(BattleManagerComponent != nullptr, TEXT("GameMode has not BattleManagerComponent"));
	if (BattleManagerComponent->IsBattle())
	{
		AMyCharacter* Target = Cast<AMyCharacter>(GetHitActor());
		if (Target != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("CharacterArrayNum : %d"), PlayerCharacterArray.Num());
			for (int i = 0; i < PlayerCharacterArray.Num(); ++i)
			{
				UBattleComponent* BattleComponent = Cast<UBattleComponent>(PlayerCharacterArray[i]->GetComponentByClass(UBattleComponent::StaticClass()));
				checkf(BattleComponent != nullptr, TEXT("Character has not BattleComponent"));
				BattleComponent->SetActionTarget(Target);
			}
		}
	}

	GameMode->LeftClick(this);
}

void AMyPlayerController::CheckFocusActor()
{
	AActor* HitActor = GetHitActor();
	GameMode->CheckFocusActor(HitActor, this);
}

AActor* AMyPlayerController::GetHitActor()
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
