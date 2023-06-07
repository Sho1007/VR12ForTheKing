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
#include "../Battle/BattleCharacterSpawnPosition.h"
#include "../Widget/BattleWidget.h"
#include "../Widget/TurnWidget.h"
#include "../Widget/BattleTurnWidget.h"


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


	// Battle Map Init
	TArray<AActor*> OutArray;

	UGameplayStatics::GetAllActorsOfClass(this, BattleMapClass, OutArray);

	///UE_LOG(LogTemp, Warning, TEXT("OutArray Length : %d"), OutArray.Num());

	for (AActor* Actor : OutArray)
	{
		BattleMapArray.Add(Cast<ABattleMap>(Actor));
	}

	CreateBattleWidget();

	UE_LOG(LogTemp, Warning, TEXT("OutArrayNum : %d, BattleMapArrayNum : %d"), OutArray.Num(), BattleMapArray.Num());

	//checkf(BattleMapArray.Num() == 0, TEXT("No BattleMap in this level"));
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
	bIsBattle = true;
	UHexGridManager* HexGridManager = Cast<UHexGridManager>(GetOwner()->GetComponentByClass(UHexGridManager::StaticClass()));
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

	UE_LOG(LogTemp, Warning, TEXT("CharacterArrayNum : %d, EnemyArrayNum : %d"), PlayerCharacterArray.Num(), EnemyClassArray.Num());

	DebugInfo();

	SpawnEnemy();
	TeleportCharacter();
	MoveCamera();
	CalculateTurn();
	AMyGameModeBase* GameModeBase = Cast<AMyGameModeBase>(GetWorld()->GetAuthGameMode());
	checkf(GameModeBase != nullptr, TEXT("GameModeBase doesn't exist"));
	GameModeBase->GetTurnWidget()->GetBattleTurnWidget()->SetTurnArray(BattleTurnArray);
	NextTurnIndex = 0;
	GameModeBase->GetTurnWidget()->GetBattleTurnWidget()->MoveToNextTurn(BattleTurnArray[NextTurnIndex]);
	
	for (int i = 0; i < BattleTurnArray.Num(); ++i)
	{
		FString CharacterName = BattleTurnArray[i]->GetName();
		
		UStatusComponent* StatusComponent = Cast<UStatusComponent>(BattleTurnArray[i]->FindComponentByClass(UStatusComponent::StaticClass()));
		UBattleComponent* BattleComponent = Cast<UBattleComponent>(BattleTurnArray[i]->FindComponentByClass(UBattleComponent::StaticClass()));
		
		EFactionType CharacterFaction = BattleComponent->GetFactionType();
		
		FString CharacterFactionName = UEnum::GetDisplayValueAsText(CharacterFaction).ToString();
		UE_LOG(LogTemp, Warning, TEXT("%s  %s  MaxHP%d  CurrentHP%d"), *CharacterFactionName, *CharacterName, StatusComponent->GetMaxHP(), StatusComponent->GetCurrentHP());
	}

	InitUnitTurn();// check whether first index of BattleTurnIndex is Enemy or not and StartUnitTurn;
	return;
}

bool UBattleManagerComponent::SetGameMode(AGameModeBase* NewGameMode)
{
	checkf(NewGameMode != nullptr, TEXT("UBattleManagerComponent::SetGameMode : NewGameMode is nullptr"));
	GameMode = NewGameMode;
	return true;
}

bool UBattleManagerComponent::IsBattle()
{
	return bIsBattle;
}



AMyCharacter* UBattleManagerComponent::GetPlayerCharacter(int32 Index)
{
	if (PlayerCharacterArray.Num() > 0 && Index < PlayerCharacterArray.Num())
	{
		return PlayerCharacterArray[Index];
	}
	else
	{
		return 0;
	}
}

int32 UBattleManagerComponent::GetPlayerCharacterArrayNum()
{
	return PlayerCharacterArray.Num();
}
	

bool UBattleManagerComponent::SpawnEnemy()
{
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
		UBattleComponent* BattleComponent = Cast<UBattleComponent>(EnemyCharacter->GetComponentByClass(UBattleComponent::StaticClass()));
		checkf(BattleComponent != nullptr, TEXT("EnemyCharacter has not BattleComponent"));
		BattleComponent->SetBaseTransform(EnemySpawnTransform);
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
		UBattleComponent* BattleComponent = Cast<UBattleComponent>(PlayerCharacterArray[i]->GetComponentByClass(UBattleComponent::StaticClass()));
		checkf(BattleComponent != nullptr, TEXT("PlayerCharacter has not BattleComponent"));
		BattleComponent->SetBaseTransform(CharacterSpawnTransform);
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
			return IP1.FindComponentByClass<UStatusComponent>()->GetSpeed() > IP2.FindComponentByClass<UStatusComponent>()->GetSpeed();
		});

	UseBattleTurnArray = BattleTurnArray;
	for (int i = 0; i < BattleTurnArray.Num(); ++i)
	{
		UseBattleTurnArray.Add(BattleTurnArray[i]);
	}
	// Todo : Do Battle Widget

}

void UBattleManagerComponent::InitUnitTurn()
{
	AMyCharacter* FirstIndexCharacter = UseBattleTurnArray[0];
	UBattleComponent* NewBattleComponent = Cast<UBattleComponent>(UseBattleTurnArray[0]->FindComponentByClass(UBattleComponent::StaticClass()));
	if (NewBattleComponent->GetFactionType() == EFactionType::Player)
	{
		checkf(UseBattleTurnArray[0] != nullptr, TEXT("UseBattleTurnArray is null"));
		BattleWidget->InitWidget(UseBattleTurnArray[0]);
		//UE_LOG(LogTemp, Warning, TEXT("BattleWidgetName %s"), *BattleWidget->GetName());
		BattleWidget->ShowWidget();
		UE_LOG(LogTemp, Warning, TEXT("%s Turn"), *UseBattleTurnArray[0]->GetName());
	}
	else if (NewBattleComponent->GetFactionType() == EFactionType::Enemy)
	{
		UE_LOG(LogTemp, Warning, TEXT("RandomEnemyAttack"));
		int32 TargerCharacterNum = FMath::RandRange(0, PlayerCharacterArray.Num() - 1);
		NewBattleComponent->SetActionTarget(PlayerCharacterArray[TargerCharacterNum]);
		NewBattleComponent->RandomEnemyAction();
	}
}

void UBattleManagerComponent::MoveToNextUnitTurn()
{

	checkf(UseBattleTurnArray.Num() != 0, TEXT("UsebattleTurnArray is empty"));
	AMyCharacter* FirstIndexCharacter = UseBattleTurnArray[0];

	
		UseBattleTurnArray.Add(FirstIndexCharacter);
		UseBattleTurnArray.RemoveAt(0);

	UBattleComponent* FisrtCharacterBattleComponent = Cast<UBattleComponent>(UseBattleTurnArray[0]->FindComponentByClass(UBattleComponent::StaticClass()));
	
	
	
	EFactionType CharacterFaction = FisrtCharacterBattleComponent->GetFactionType();
	FString CharacterFactionName = UEnum::GetDisplayValueAsText(CharacterFaction).ToString();// Get FactionType of BattleTurnArray[0] and change it to string

	if (FisrtCharacterBattleComponent->GetFactionType() == EFactionType::Player)
	{
		
		checkf(UseBattleTurnArray[0] != nullptr, TEXT("UseBattleTurnArray is null"));
		BattleWidget->InitWidget(UseBattleTurnArray[0]);
		//UE_LOG(LogTemp, Warning, TEXT("BattleWidgetName %s"), *BattleWidget->GetName());
		BattleWidget->ShowWidget();
		
		UE_LOG(LogTemp, Warning, TEXT("%s  %s Turn"),*CharacterFactionName, *UseBattleTurnArray[0]->GetName());
	}
	else if (FisrtCharacterBattleComponent->GetFactionType() == EFactionType::Enemy)
	{
		
		checkf(UseBattleTurnArray[0] != nullptr, TEXT("UseBattleTurnArray is null"));
		UE_LOG(LogTemp, Warning, TEXT("%s  %s RandomEnemyAttack"), *CharacterFactionName, *UseBattleTurnArray[0]->GetName());
		int32 TargerCharacterNum = FMath::RandRange(0, PlayerCharacterArray.Num() - 1);
		FisrtCharacterBattleComponent->SetActionTarget(PlayerCharacterArray[TargerCharacterNum]);
		FisrtCharacterBattleComponent->RandomEnemyAction();
	}
}


void UBattleManagerComponent::RemoveDeadUnitFromArray()
{
	UE_LOG(LogTemp, Warning, TEXT("RemoveDeadUnitFromArray called"));
    checkf(UseBattleTurnArray.Num() != 0, TEXT("UseBattleTurnArray is Empty"));
	
		for (int i = 0; i < UseBattleTurnArray.Num();)
		{
			UBattleComponent* NewBattleComponent = Cast<UBattleComponent>(UseBattleTurnArray[i]->FindComponentByClass(UBattleComponent::StaticClass()));
			if (NewBattleComponent->IsDead() == true)
			{
				if (NewBattleComponent->GetFactionType() == EFactionType::Player)
				{
					++DeadPlayerCount;
					
				}
				else if (NewBattleComponent->GetFactionType() == EFactionType::Enemy)
				{
					++DeadEnemyCount;
				}
				UseBattleTurnArray.RemoveAt(i);
			}
			else if (NewBattleComponent->IsDead() == false)
			{
				++i;
			}
			UE_LOG(LogTemp, Warning, TEXT("ArrayNum %d"), UseBattleTurnArray.Num());
		}

		if (DeadEnemyCount / 2 == EnemyCharacterArray.Num())
		{
			EndBattle();
		}
		if (DeadPlayerCount / 2 == PlayerCharacterArray.Num())
		{
			GameOver();
		}

		UE_LOG(LogTemp, Warning, TEXT("DeadPlayer %d   DeadEnemy %d"), DeadPlayerCount/2, DeadEnemyCount/2);


}

void UBattleManagerComponent::ResurrectCharacter(AMyCharacter* ResurrectCharacter)
{
	for (int32 i = 0; i < 2; ++i)
	{
		UseBattleTurnArray.Add(ResurrectCharacter);
		--DeadPlayerCount;
	}



	UseBattleTurnArray.Sort([](const AMyCharacter& IP1, const AMyCharacter& IP2)
	{
			// Todo : Implement Calculateturn Logic
			return IP1.FindComponentByClass<UStatusComponent>()->GetSpeed() > IP2.FindComponentByClass<UStatusComponent>()->GetSpeed();
	});

	TArray<AMyCharacter*> TempArray;
	for (int32 i = 0; i < UseBattleTurnArray.Num(); ++i)
	{
		if (i % 2 == 0)
		{
			TempArray.Add(UseBattleTurnArray[i]);
			UseBattleTurnArray.RemoveAt(i);
		}
	}
	for (int i = 0; i < TempArray.Num(); ++i)
	{
		UseBattleTurnArray.Add(TempArray[i]);
	}

	UStatusComponent* NewStatusComponent = Cast<UStatusComponent>(ResurrectCharacter->FindComponentByClass(UStatusComponent::StaticClass()));
	NewStatusComponent->SetCurrentHP(1);
	
	for (int i = 0; i < UseBattleTurnArray.Num(); ++i)
	{
		FString CharacterName = UseBattleTurnArray[i]->GetName();

		UStatusComponent* StatusComponent = Cast<UStatusComponent>(UseBattleTurnArray[i]->FindComponentByClass(UStatusComponent::StaticClass()));
		UBattleComponent* BattleComponent = Cast<UBattleComponent>(UseBattleTurnArray[i]->FindComponentByClass(UBattleComponent::StaticClass()));

		EFactionType CharacterFaction = BattleComponent->GetFactionType();

		FString CharacterFactionName = UEnum::GetDisplayValueAsText(CharacterFaction).ToString();
		UE_LOG(LogTemp, Warning, TEXT("%s  %s  MaxHP%d  CurrentHP%d"), *CharacterFactionName, *CharacterName, StatusComponent->GetMaxHP(), StatusComponent->GetCurrentHP());
	}

	UE_LOG(LogTemp, Warning, TEXT("ArrayNum %d"), UseBattleTurnArray.Num());
}


void UBattleManagerComponent::CreateBattleWidget()
{
	check(BattleWidgetClass != nullptr);
	BattleWidget = CreateWidget<UBattleWidget>(GetWorld()->GetFirstPlayerController(), BattleWidgetClass);
	check(BattleWidget != nullptr);
	BattleWidget->AddToPlayerScreen(0);
	BattleWidget->HideWidget();
}

void UBattleManagerComponent::EndBattle()
{
	UE_LOG(LogTemp, Warning, TEXT("Victory!!"));
}

void UBattleManagerComponent::GameOver()
{
	UE_LOG(LogTemp, Warning, TEXT("GameOver!!"));
}
