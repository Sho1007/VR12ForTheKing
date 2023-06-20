// Fill out your copyright notice in the Description page of Project Settings.


#include "../GameMode/MoveBoardGameMode.h"

#include "../MyGameInstance.h"
#include "../GameState/MoveBoardGameState.h"
#include "../Component/BattleManagerComponent.h"
#include "../Component/MoveManagerComponent.h"
#include "../Event/TileEventManager.h"
#include "../HexGrid/HexGridManager.h"

#include "../Character/MyCharacter.h"

AMoveBoardGameMode::AMoveBoardGameMode()
	: Super()
{
	PrimaryActorTick.SetTickFunctionEnable(false);
}

void AMoveBoardGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void AMoveBoardGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());
	check(MyGameInstance);
	
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Cyan, FString::Printf(TEXT("%s's Index : %d"), *NewPlayer->GetName(), MyGameInstance->FindPlayerControllerIndex(NewPlayer)));
}

void AMoveBoardGameMode::HandleSeamlessTravelPlayer(AController*& C)
{
	Super::HandleSeamlessTravelPlayer(C);
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("AMoveBoardGameMode::HandleSeamlessTravelPlayer")));
}