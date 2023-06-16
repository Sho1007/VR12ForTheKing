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
	// BattleManager
	BattleManager = CreateDefaultSubobject<UBattleManagerComponent>(TEXT("BattleManager"));
	check(BattleManager != nullptr);
	BattleManager->SetGameMode(this);

	// MoveManager
	MoveManager = CreateDefaultSubobject<UMoveManagerComponent>(TEXT("MoveManager"));
	check(MoveManager != nullptr);

	// HexGridManager
	HexGridManager = CreateDefaultSubobject<UHexGridManager>(TEXT("HexGridManager"));
	check(HexGridManager != nullptr);

	// TileEventManager
	TileEventManager = CreateDefaultSubobject<UTileEventManager>(TEXT("TileEventManager"));
	check(TileEventManager != nullptr);

	bIsInit = false;
	PrimaryActorTick.SetTickFunctionEnable(false);
}

void AMoveBoardGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (bIsInit == false)
	{
		InitGameMode();
	}
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

void AMoveBoardGameMode::InitGameMode()
{
	MoveManager->Init();

	// Todo : Check is MoveBoardMap to Show and Hide
	HexGridManager->CreateGrid();
}

void AMoveBoardGameMode::CreatePlayer()
{
	TArray<AMyCharacter*>& PlayerCharacterArray = GetGameState<AMoveBoardGameState>()->GetPlayerCharacterArray();

	GetWorld()->SpawnActor<AMyCharacter>();

	//PlayerCharacterArray.Add();
}