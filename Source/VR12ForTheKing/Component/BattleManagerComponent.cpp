// Fill out your copyright notice in the Description page of Project Settings.


#include "../Component/BattleManagerComponent.h"

#include "../Character/MyCharacter.h"
#include "Kismet/GamePlayStatics.h"
#include "Camera/CameraComponent.h"

#include "../MyGameModeBase.h"
#include "../HexGrid/HexGridManager.h"
#include "../HexGrid/HexTile.h"
#include "../Event/EnemyEventActor.h"
#include "BattleComponent.h"
#include "StatusComponent.h"
#include "../Battle/BattleMap.h"


// Sets default values for this component's properties
UBattleManagerComponent::UBattleManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UBattleManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	TArray<AActor*> OutArray;

	UGameplayStatics::GetAllActorsOfClass(this, BattleMapClass, OutArray);

	///UE_LOG(LogTemp, Warning, TEXT("OutArray Length : %d"), OutArray.Num());

	for (AActor* Actor : OutArray)
	{
		BattleMapArray.Add(Cast<ABattleMap>(Actor));
	}
}

// Called every frame
void UBattleManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBattleManagerComponent::AddEnemyClass(const TSubclassOf<AMyCharacter> NewEnemyClass)
{
	UE_LOG(LogTemp, Warning, TEXT("UBattleManagerComponent::AddEnemyClass : Called"));
	EnemyClassArray.Add(NewEnemyClass);
}

void UBattleManagerComponent::AddPlayerCharacter(AMyCharacter* NewPlayerCharacter)
{
	UE_LOG(LogTemp, Warning, TEXT("UBattleManagerComponent::AddPlayerCharacter : Called"));
	PlayerCharacterArray.Add(NewPlayerCharacter);
}

void UBattleManagerComponent::DebugInfo()
{
	UE_LOG(LogTemp, Warning, TEXT("UBattleManagerComponent::DebugInfo : Player %d"), PlayerCharacterArray.Num());
	for (auto Iter : PlayerCharacterArray)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Iter->GetName());
	}

	UE_LOG(LogTemp, Warning, TEXT("UBattleManagerComponent::DebugInfo : Enemy %d"), EnemyClassArray.Num());
	for (auto Iter : EnemyClassArray)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Iter->GetName());
	}
}

void UBattleManagerComponent::InitBattle(AActor* BattleTile)
{
	// Clear Variable
	PlayerCharacterArray.Empty();
	EnemyCharacterArray.Empty();
	EnemyClassArray.Empty();
	SpawnEnemyIndex = 0;


	AHexGridManager* HexGridManager = Cast<AMyGameModeBase>(GameMode)->GetHexGridManager();
	checkf(HexGridManager != nullptr, TEXT("UBattleManagerComponent::InitBattle : HexGridManager is nullptr"));

	AHexTile* CurrentTile = Cast<AHexTile>(BattleTile);
	checkf(CurrentTile != nullptr, TEXT("UBattleManagerComponent::InitBattle : BattleTile is not AHexTile Class"));

	AEnemyEventActor* EnemyEventActor = Cast<AEnemyEventActor>(CurrentTile->GetTileEvent());
	checkf(EnemyEventActor != nullptr, TEXT("UBattleManagerComponent::InitBattle : EnemyEventActor is invalid"));
	
	TArray<TSubclassOf<AMyCharacter>> CurrentEnemyClassArray;

	TArray<AHexTile*> NeighborTileArray;

	HexGridManager->FindNeighborTiles(NeighborTileArray, CurrentTile, 2);

	for (AHexTile* NeighborTile : NeighborTileArray)
	{
		if (!NeighborTile->GetIsSearched()) continue;
		TArray<AMyCharacter*> InTileCharacterArray = NeighborTile->GetInTileCharacterArray();
		
		for (AMyCharacter* InTileCharacter : InTileCharacterArray)
		{
			UBattleComponent* BattleComponent = InTileCharacter->FindComponentByClass<UBattleComponent>();
			if (BattleComponent != nullptr && BattleComponent->GetFactionType() == EFactionType::Player)
			{
				AddPlayerCharacter(InTileCharacter);
			}
		}

		EnemyEventActor = Cast<AEnemyEventActor>(NeighborTile->GetTileEvent());
		if (EnemyEventActor == nullptr) continue;
		CurrentEnemyClassArray = EnemyEventActor->GetEnemyArray();
		for (TSubclassOf<AMyCharacter> EnemyClass : CurrentEnemyClassArray)
		{
			AddEnemyClass(EnemyClass);
		}
	}

	DebugInfo();

	SpawnEnemy();
	TeleportCharacter();
	MoveCamera();
}

bool UBattleManagerComponent::SetGameMode(AGameModeBase* NewGameMode)
{
	checkf(NewGameMode != nullptr, TEXT("UBattleManagerComponent::SetGameMode : NewGameMode is nullptr"));
	GameMode = NewGameMode;
	return true;
}

bool UBattleManagerComponent::SpawnEnemy()
{
	// Todo : Set BattleMap

	int32 SpawnEnemyCount = 0;

	for (; SpawnEnemyCount < 3; ++SpawnEnemyCount)
	{
		if (SpawnEnemyCount + SpawnEnemyIndex >= EnemyClassArray.Num())
		{
			SpawnEnemyIndex += SpawnEnemyCount;
			return true;
		}

		FTransform EnemySpawnTransform = BattleMapArray[0]->GetEnemySpawnPosition()[SpawnEnemyCount]->GetActorTransform();
		AMyCharacter* EnemyCharacter = GetWorld()->SpawnActor<AMyCharacter>(EnemyClassArray[SpawnEnemyCount + SpawnEnemyIndex], EnemySpawnTransform);
		checkf(EnemyCharacter != nullptr, TEXT("UBattleManagerComponent::SpawnEnemy : EnemyCharacter is not spawned"));
		EnemyCharacterArray.Add(EnemyCharacter);
	}

	SpawnEnemyIndex += SpawnEnemyCount + 1;
	return true;
}

bool UBattleManagerComponent::TeleportCharacter()
{
	for (int i = 0; i < PlayerCharacterArray.Num(); ++i)
	{
		FTransform CharacterSpawnTransform = BattleMapArray[0]->GetPlayerSpawnPosition()[i]->GetActorTransform();
		PlayerCharacterArray[i]->SetActorTransform(CharacterSpawnTransform);
	}

	return true;
}

void UBattleManagerComponent::MoveCamera()
{
	APlayerController* LocalPlayerController = GEngine->GetFirstLocalPlayerController(GetWorld());
	APawn* LocalPawn = LocalPlayerController->GetPawn();
	LocalPawn->SetActorLocation(BattleMapArray[0]->GetNeutralSideCamera()->GetActorLocation());
	LocalPawn->FindComponentByClass<UCameraComponent>()->SetWorldRotation(BattleMapArray[0]->GetNeutralSideCamera()->GetActorRotation());
}

void UBattleManagerComponent::CalculateTurn()
{
	BattleTurnArray.Empty();
	for (int i = 0; i < EnemyCharacterArray.Num(); ++i)
	{
		BattleTurnArray.Add(EnemyCharacterArray[i]);
	}
	for (int i = 0; i < PlayerCharacterArray.Num(); ++i)
	{
		BattleTurnArray.Add(PlayerCharacterArray[i]);
	}
	BattleTurnArray.Sort([](const AMyCharacter& IP1, const AMyCharacter& IP2)
		{
			// Todo : Implement Calculateturn Logic
			return IP1.FindComponentByClass<UStatusComponent>()->GetCharacterStatus().Speed > IP2.FindComponentByClass<UStatusComponent>()->GetCharacterStatus().Speed;
		});

	// Todo : Do Battle Widget
}