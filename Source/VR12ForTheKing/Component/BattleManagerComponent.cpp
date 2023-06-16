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

//#include "TimerManager.h"


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
	TargetPlayerArray.Empty();
	SpawnEnemyIndex = 0;
	bIsBattle = true;
	MapIndex = 0;
	VictoryCount = 0;
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
	TargetPlayerArray = PlayerCharacterArray;
	//DebugInfo();


	SpawnEnemy();
	TeleportCharacter();
	MoveCamera(BattleMapArray[MapIndex]->GetNeutralSideCamera()->GetActorTransform());
	CalculateTurn();
	AMyGameModeBase* GameModeBase = Cast<AMyGameModeBase>(GetWorld()->GetAuthGameMode());
	checkf(GameModeBase != nullptr, TEXT("GameModeBase doesn't exist"));
	GameModeBase->GetTurnWidget()->GetBattleTurnWidget()->SetTurnArray(UseBattleTurnArray);
	

	for (int i = 0; i < BattleTurnArray.Num(); ++i)
	{
		if (UseBattleTurnArray[i] != nullptr)
		{
			FString CharacterName = BattleTurnArray[i]->GetName();

			UStatusComponent* StatusComponent = Cast<UStatusComponent>(BattleTurnArray[i]->FindComponentByClass(UStatusComponent::StaticClass()));
			UBattleComponent* BattleComponent = Cast<UBattleComponent>(BattleTurnArray[i]->FindComponentByClass(UBattleComponent::StaticClass()));

			EFactionType CharacterFaction = BattleComponent->GetFactionType();

			FString CharacterFactionName = UEnum::GetDisplayValueAsText(CharacterFaction).ToString();
			UE_LOG(LogTemp, Warning, TEXT("%s  %s  MaxHP%d  CurrentHP%d"), *CharacterFactionName, *CharacterName, StatusComponent->GetMaxHP(), StatusComponent->GetCurrentHP());
		}
		else
		{
			continue;
		}
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

UBattleWidget* UBattleManagerComponent::GetBattleWidget()
{
	return BattleWidget;
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
	

		FTransform EnemySpawnTransform = BattleMapArray[MapIndex]->GetEnemySpawnPosition()[SpawnEnemyCount]->GetActorTransform();
		AMyCharacter* EnemyCharacter = GetWorld()->SpawnActor<AMyCharacter>(EnemyClassArray[SpawnEnemyCount + SpawnEnemyIndex], EnemySpawnTransform);
		UBattleComponent* BattleComponent = Cast<UBattleComponent>(EnemyCharacter->GetComponentByClass(UBattleComponent::StaticClass()));
		checkf(BattleComponent != nullptr, TEXT("EnemyCharacter has not BattleComponent"));
		BattleComponent->SetBaseTransform(EnemySpawnTransform);
		BattleComponent->SetTargetCamera(BattleMapArray[MapIndex]->GetEnemySpawnPosition()[SpawnEnemyCount]->GetCameraPosition());
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
		FTransform CharacterSpawnTransform = BattleMapArray[MapIndex]->GetPlayerSpawnPosition()[i]->GetActorTransform();
		PlayerCharacterArray[i]->SetActorTransform(CharacterSpawnTransform);
		UBattleComponent* BattleComponent = Cast<UBattleComponent>(PlayerCharacterArray[i]->GetComponentByClass(UBattleComponent::StaticClass()));
		checkf(BattleComponent != nullptr, TEXT("PlayerCharacter has not BattleComponent"));
		BattleComponent->SetTargetCamera(BattleMapArray[MapIndex]->GetPlayerSpawnPosition()[i]->GetCameraPosition());
		BattleComponent->SetBaseTransform(CharacterSpawnTransform);
	}

	return true;
}

void UBattleManagerComponent::MoveCamera(FTransform TargetCameraTransform)
{
	APlayerController* LocalPlayerController = GEngine->GetFirstLocalPlayerController(GetWorld());
	APawn* LocalPawn = LocalPlayerController->GetPawn();
	LocalPawn->SetActorLocation(TargetCameraTransform.GetLocation());
	LocalPawn->FindComponentByClass<UCameraComponent>()->SetWorldRotation(TargetCameraTransform.GetRotation());
	/*LocalPawn->SetActorLocation(BattleMapArray[0]->GetNeutralSideCamera()->GetActorLocation());
	LocalPawn->FindComponentByClass<UCameraComponent>()->SetWorldRotation(BattleMapArray[0]->GetNeutralSideCamera()->GetActorRotation());*/
}

void UBattleManagerComponent::MoveLerpCamera(FTransform TargetCameraTransform)
{
	APlayerController* LocalPlayerController = GEngine->GetFirstLocalPlayerController(GetWorld());
	APawn* LocalPawn = LocalPlayerController->GetPawn();

	
	TargetLocation = TargetCameraTransform.GetLocation();
	TargetRotation = TargetCameraTransform.GetRotation().Rotator();
	UE_LOG(LogTemp, Warning, TEXT("%s"), *TargetRotation.ToString());

	GetWorld()->GetTimerManager().ClearTimer(CameraLerpTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(CameraLerpTimerHandle, this, &UBattleManagerComponent::LerpTimerFunction, 0.01f, true);
}

void UBattleManagerComponent::LerpTimerFunction()
{
	APlayerController* LocalPlayerController = GEngine->GetFirstLocalPlayerController(GetWorld());
	APawn* LocalPawn = LocalPlayerController->GetPawn();

	LocalPawn->SetActorLocation(FMath::Lerp(LocalPawn->GetActorLocation(), TargetLocation, 0.01f));
	LocalPawn->FindComponentByClass<UCameraComponent>()->SetRelativeRotation(FMath::Lerp(LocalPawn->FindComponentByClass<UCameraComponent>()->GetRelativeRotation(), TargetRotation, 0.01f));
	
	if (LocalPawn->GetActorLocation() == TargetLocation)
	{
		GetWorld()->GetTimerManager().ClearTimer(CameraLerpTimerHandle);
	}
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
	UseBattleTurnArray.Add(nullptr);
	for (int i = 0; i < BattleTurnArray.Num(); ++i)
	{
		UseBattleTurnArray.Add(BattleTurnArray[i]);
	}
	UseBattleTurnArray.Add(nullptr);
	// Todo : Do Battle Widget

}

void UBattleManagerComponent::InitUnitTurn()
{


	AMyCharacter* FirstIndexCharacter = UseBattleTurnArray[0];
	UBattleComponent* NewBattleComponent = Cast<UBattleComponent>(UseBattleTurnArray[0]->FindComponentByClass(UBattleComponent::StaticClass()));
	if (NewBattleComponent->GetFactionType() == EFactionType::Player)
	{
		//checkf(UseBattleTurnArray[0] != nullptr, TEXT("UseBattleTurnArray is null"));

		BattleWidget->InitWidget(UseBattleTurnArray[0]);
		//UE_LOG(LogTemp, Warning, TEXT("BattleWidgetName %s"), *BattleWidget->GetName());
		BattleWidget->ShowWidget();
		UE_LOG(LogTemp, Warning, TEXT("%s Turn"), *UseBattleTurnArray[0]->GetName());


	}
	else if (NewBattleComponent->GetFactionType() == EFactionType::Enemy)
	{
		
	
		if (TargetPlayerArray.Num() != 0) // check if TargetPlayerArray is notempty
		{

		  int32 TargerCharacterNum = FMath::RandRange(0, TargetPlayerArray.Num() - 1); // Get Random Index In TargetCharacter Array
		  UE_LOG(LogTemp, Warning, TEXT("%s  RandomEnemyAttack"), *UseBattleTurnArray[0]->GetName()); // enemyunit random attack
		  NewBattleComponent->SetActionTarget(TargetPlayerArray[TargerCharacterNum]); // set ActionTarget At TargetCharacter Array
		  NewBattleComponent->DoAction(); // Do RandomEnemyAttack
		
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Target is not exist"));
		}
	
	}

	UE_LOG(LogTemp, Warning, TEXT("TargetPlayer num %d"), TargetPlayerArray.Num());
}

void UBattleManagerComponent::MoveToNextUnitTurn()
{
	UE_LOG(LogTemp, Warning, TEXT("MoveToNextUnitTurn"));

	checkf(UseBattleTurnArray.Num() != 0, TEXT("UsebattleTurnArray is empty"));


	AMyCharacter* FirstIndexCharacter = UseBattleTurnArray[0];

	AMyGameModeBase* GameModeBase = Cast<AMyGameModeBase>(GetWorld()->GetAuthGameMode());
	checkf(GameModeBase != nullptr, TEXT("GameModeBase doesn't exist"));
	GameModeBase->GetTurnWidget()->GetBattleTurnWidget()->MoveToNextTurn(UseBattleTurnArray[0]);
	checkf(UseBattleTurnArray.Num() != 0, TEXT("UsebattleTurnArray is empty"));

	UseBattleTurnArray.Add(FirstIndexCharacter); //Move FirstIndex of UseBattleTurnArray to LastIndex of UseBattleTurnArray;
	UseBattleTurnArray.RemoveAt(0);


	if (UseBattleTurnArray[0] != nullptr)
	{
		UBattleComponent* FirstCharacterBattleComponent = Cast<UBattleComponent>(UseBattleTurnArray[0]->FindComponentByClass(UBattleComponent::StaticClass()));
		EFactionType CharacterFaction = FirstCharacterBattleComponent->GetFactionType();
		FString CharacterFactionName = UEnum::GetDisplayValueAsText(CharacterFaction).ToString();// Get FactionType of BattleTurnArray[0] and change it to string

		MoveLerpCamera(FirstCharacterBattleComponent->GetTargetCamera()->GetActorTransform());
		if (FirstCharacterBattleComponent->GetFactionType() == EFactionType::Player) // initwidget to select action
		{
			
			//checkf(UseBattleTurnArray[0] != nullptr, TEXT("UseBattleTurnArray is null"));
			BattleWidget->InitWidget(UseBattleTurnArray[0]);
			//UE_LOG(LogTemp, Warning, TEXT("BattleWidgetName %s"), *BattleWidget->GetName());
			BattleWidget->ShowWidget();

			UE_LOG(LogTemp, Warning, TEXT("%s  %s Turn"), *CharacterFactionName, *UseBattleTurnArray[0]->GetName());
		}
		else if (FirstCharacterBattleComponent->GetFactionType() == EFactionType::Enemy)
		{

			if (TargetPlayerArray.Num() != 0) // check if TargetPlayerArray is notempty
			{
				int32 TargerCharacterNum = FMath::RandRange(0, TargetPlayerArray.Num() - 1);
				UE_LOG(LogTemp, Warning, TEXT("%s  %s RandomEnemyAttack"), *CharacterFactionName, *UseBattleTurnArray[0]->GetName()); // enemyunit random attack
				FirstCharacterBattleComponent->SetActionTarget(TargetPlayerArray[TargerCharacterNum]);
				FirstCharacterBattleComponent->DoAction();
				
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Target is not exist"));
			}
			
		
		}
		UE_LOG(LogTemp, Warning, TEXT("TargetPlayer num %d"), TargetPlayerArray.Num());

	}
	else if (UseBattleTurnArray[0] == nullptr) // if FirstIndex is nullptr Remove it and add to end
	{
		GameModeBase->GetTurnWidget()->GetBattleTurnWidget()->MoveToNextTurn(UseBattleTurnArray[0]);
		checkf(UseBattleTurnArray.Num() != 0, TEXT("UsebattleTurnArray is empty"));

		UseBattleTurnArray.Add(nullptr);
		UseBattleTurnArray.RemoveAt(0);

		UBattleComponent* FirstCharacterBattleComponent = Cast<UBattleComponent>(UseBattleTurnArray[0]->FindComponentByClass(UBattleComponent::StaticClass()));
		EFactionType CharacterFaction = FirstCharacterBattleComponent->GetFactionType();
		FString CharacterFactionName = UEnum::GetDisplayValueAsText(CharacterFaction).ToString();// Get FactionType of BattleTurnArray[0] and change it to string
		MoveLerpCamera(FirstCharacterBattleComponent->GetTargetCamera()->GetActorTransform());
		if (FirstCharacterBattleComponent->GetFactionType() == EFactionType::Player)
		{

			checkf(UseBattleTurnArray[0] != nullptr, TEXT("UseBattleTurnArray is null"));
			BattleWidget->InitWidget(UseBattleTurnArray[0]);
			//UE_LOG(LogTemp, Warning, TEXT("BattleWidgetName %s"), *BattleWidget->GetName());
			BattleWidget->ShowWidget();
			UE_LOG(LogTemp, Warning, TEXT("%s  %s Turn"), *CharacterFactionName, *UseBattleTurnArray[0]->GetName());
		}
		else if (FirstCharacterBattleComponent->GetFactionType() == EFactionType::Enemy)
		{

			checkf(UseBattleTurnArray[0] != nullptr, TEXT("UseBattleTurnArray is null"));
			if (TargetPlayerArray.Num() != 0) // check if TargetPlayerArray is notempty
			{
				UE_LOG(LogTemp, Warning, TEXT("%s  %s RandomEnemyAttack"), *CharacterFactionName, *UseBattleTurnArray[0]->GetName());
				int32 TargerCharacterNum = FMath::RandRange(0, TargetPlayerArray.Num() - 1);
				FirstCharacterBattleComponent->SetActionTarget(TargetPlayerArray[TargerCharacterNum]);
				FirstCharacterBattleComponent->DoAction();
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Target is not exist"));
			}
			

		}

		UE_LOG(LogTemp, Warning, TEXT("TargetPlayer num %d"), TargetPlayerArray.Num());
	}


	for (int i = 0; i < UseBattleTurnArray.Num(); ++i) // show battleturnarray on log
	{
		if (UseBattleTurnArray[i] != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT(" % s"), *UseBattleTurnArray[i]->GetName());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Null"));
		}
	}

		
}


void UBattleManagerComponent::RemoveDeadUnitFromArray(AMyCharacter* TargetCharacter)
{
	UE_LOG(LogTemp, Warning, TEXT("RemoveDeadUnitFromArray called"))
	checkf(UseBattleTurnArray.Num() != 0, TEXT("UseBattleTurnArray is Empty"));

	AMyGameModeBase* GameModeBase = Cast<AMyGameModeBase>(GetWorld()->GetAuthGameMode());
	checkf(GameModeBase != nullptr, TEXT("GameModeBase doesn't exist"));

	UBattleComponent* BattleComponent = Cast<UBattleComponent>(TargetCharacter->FindComponentByClass(UBattleComponent::StaticClass()));
	if (BattleComponent->GetFactionType() == EFactionType::Player)
	{
		++DeadPlayerCount; // Add Deadcount When Player Dead

		if (TargetPlayerArray.Num() != 0) // Check TargetArray is empty or not
		{
			for (int i = 0; i < TargetPlayerArray.Num();) // Remove DeadCharacter From TargetArray
			{
				if (TargetPlayerArray[i] == TargetCharacter)
				{
					TargetPlayerArray.RemoveAt(i);
					break;
				}
				else
				{
					++i;
				}
			}
		}
		
	  
	}
	else if (BattleComponent->GetFactionType() == EFactionType::Enemy)
	{
		++DeadEnemyCount;

		
	}

	for (int i = 0; i < UseBattleTurnArray.Num();)
	{
		if (UseBattleTurnArray[i] == TargetCharacter)
		{
			GameModeBase->GetTurnWidget()->GetBattleTurnWidget()->RemoveUnitFromImageArray(i); // Remove DeadUnitFrom Widget ImageArray
			UseBattleTurnArray.RemoveAt(i); // RemoveUnitFrom TurnArray
			UE_LOG(LogTemp, Warning, TEXT("%s Dead"), *TargetCharacter->GetName()); // Get Name of Dead Character
		}
		else if((UseBattleTurnArray[i] != TargetCharacter))
		{
			++i;
			//UE_LOG(LogTemp, Warning, TEXT("%d "), i);
		}
	}

	if (DeadEnemyCount == EnemyCharacterArray.Num())
	{
		
		EndBattle(); // Check Victory
	}
	if (DeadPlayerCount == PlayerCharacterArray.Num())
	{
		GameOver(); // Check GameOver
	}


	for (int i = 0; i < UseBattleTurnArray.Num(); ++i) // show battleturnarray on log
	{
		if (UseBattleTurnArray[i] != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT(" % s"), *UseBattleTurnArray[i]->GetName());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Null"));
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("DeadPlayer %d   DeadEnemy %d"), DeadPlayerCount, DeadEnemyCount);
	UE_LOG(LogTemp, Warning, TEXT("UseBattleTurnArrayNum %d"), UseBattleTurnArray.Num());
}

void UBattleManagerComponent::ResetActionTargetWhenEnemyDead()
{

	checkf(UseBattleTurnArray.Num() != 0, TEXT("UseBattleTurnArray is Empty"));
	AMyGameModeBase* GameModeBase = Cast<AMyGameModeBase>(GetWorld()->GetAuthGameMode());
	checkf(GameModeBase != nullptr, TEXT("GameModeBase doesn't exist"));

	for (int i = 0; i < UseBattleTurnArray.Num(); ++i)
	{
		if (UseBattleTurnArray[i] != nullptr)
		{
			UBattleComponent* NewBattleComponent = Cast<UBattleComponent>(UseBattleTurnArray[i]->FindComponentByClass(UBattleComponent::StaticClass()));
			if (NewBattleComponent->GetFactionType() == EFactionType::Player)
			{
				NewBattleComponent->SetActionTarget(nullptr);
			}
		}

	}
}

void UBattleManagerComponent::ResurrectCharacter(AMyCharacter* ResurrectCharacter)
{
	UStatusComponent* NewStatusComponent = Cast<UStatusComponent>(ResurrectCharacter->FindComponentByClass(UStatusComponent::StaticClass()));
	NewStatusComponent->SetCurrentHP(1);

	AMyGameModeBase* GameModeBase = Cast<AMyGameModeBase>(GetWorld()->GetAuthGameMode());
	checkf(GameModeBase != nullptr, TEXT("GameModeBase doesn't exist"));

	for (int32 i = 1; i < UseBattleTurnArray.Num(); ++i)
	{
		if (UseBattleTurnArray[i] == nullptr
			|| Cast<UStatusComponent>(UseBattleTurnArray[i]->FindComponentByClass(UStatusComponent::StaticClass()))->GetSpeed() < NewStatusComponent->GetSpeed())
		{
			UseBattleTurnArray.Insert(ResurrectCharacter, i); 
			GameModeBase->GetTurnWidget()->GetBattleTurnWidget()->AddUnitToImageArray(UseBattleTurnArray);
			checkf(UseBattleTurnArray.Num() != 0, TEXT("UsebattleTurnArray is empty"));
			break;
		}
	}

	int32 SecondPos = 0;

	for (int32 i = 1; i < UseBattleTurnArray.Num(); ++i)
	{
		if (UseBattleTurnArray[i] == nullptr)
		{
			SecondPos = i + 1;
			break;
		}
	}

	for (int32 i = SecondPos; i < UseBattleTurnArray.Num(); ++i)
	{
		if (UseBattleTurnArray[i] == nullptr
			|| Cast<UStatusComponent>(UseBattleTurnArray[i]->FindComponentByClass(UStatusComponent::StaticClass()))->GetSpeed() < NewStatusComponent->GetSpeed())
		{
			UseBattleTurnArray.Insert(ResurrectCharacter, i);
			GameModeBase->GetTurnWidget()->GetBattleTurnWidget()->AddUnitToImageArray(UseBattleTurnArray);
			break;
		}
	}


	for (int i = 0; i < UseBattleTurnArray.Num(); ++i) // show battleturnarray on log
	{
		if (UseBattleTurnArray[i] != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT(" % s"), *UseBattleTurnArray[i]->GetName());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Null"));
		}
	}




	UE_LOG(LogTemp, Warning, TEXT("ArrayNum %d"), UseBattleTurnArray.Num());
	GameModeBase->GetTurnWidget()->DeleteHeartCount();

	DeadPlayerCount -= DeadPlayerCount;
	TargetPlayerArray.Add(ResurrectCharacter);
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
	++VictoryCount;
	UE_LOG(LogTemp, Warning, TEXT("Victory!!"));
	BattleMapArray[MapIndex]->MoveNextSceneIndex();
	TeleportCharacter();
	SpawnEnemy();
	MoveCamera(BattleMapArray[MapIndex]->GetNeutralSideCamera()->GetActorTransform());

	UWorld* World = GetWorld();


	if (VictoryCount == 1)
	{
		World->ServerTravel("/Game/Develop/Jino/Map/CPPTestMap");
	}

}

void UBattleManagerComponent::GameOver()
{
	UE_LOG(LogTemp, Warning, TEXT("GameOver!!"));
}
