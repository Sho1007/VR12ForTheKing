// Fill out your copyright notice in the Description page of Project Settings.


#include "../Component/BattleManagerComponent.h"
#include "Engine/DataTable.h"
#include "../Character/MyCharacter.h"
#include "Kismet/GamePlayStatics.h"
#include "Camera/CameraComponent.h"

#include "Net/UnrealNetwork.h"

//#include "../MyGameModeBase.h"
#include "../HexGrid/HexGridManager.h"
#include "../HexGrid/HexTile.h"
#include "../Event/EnemyEventActor.h"
#include "BattleComponent.h"
#include "StatusComponent.h"
#include "InventoryComponent.h"
#include "../Battle/BattleMap.h"
#include "../Battle/BattleCharacterSpawnPosition.h"
#include "../Widget/BattleWidget.h"
#include "../Widget/TurnWidget.h"
#include "../Widget/BattleTurnWidget.h"
#include "../Widget/VictoryWidget.h"
#include "../Widget/VictoryWidgetSlot.h"
#include "Components/SkeletalMeshComponent.h"

#include "../PlayerController/MoveBoardPlayerController.h"
#include "../HUD/MoveBoardHUD.h"
#include "../GameState/MoveBoardGameState.h"

#include "LevelSequence.h"
#include "LevelSequencePlayer.h"
#include "LevelSequenceActor.h"

// Sets default values for this component's properties
UBattleManagerComponent::UBattleManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicated(true);
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

	UE_LOG(LogTemp, Warning, TEXT("OutArrayNum : %d, BattleMapArrayNum : %d"), OutArray.Num(), BattleMapArray.Num());

	checkf(BattleMapArray.Num() != 0, TEXT("No BattleMap in this level"));
}

void UBattleManagerComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UBattleManagerComponent, CurrentTurnCharacter);
}

void UBattleManagerComponent::PlayLevelSequnce()
{
	TArray<AActor*> LevelSequenceActorArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALevelSequenceActor::StaticClass(), LevelSequenceActorArray);

	LevelSequenceActor = Cast<ALevelSequenceActor>(LevelSequenceActorArray[0]);
	LevelSequenceActor->GetSequencePlayer()->Play();
}

void UBattleManagerComponent::PlayAnimation(FName TargetAnimName)
{
	
	//checkf(PlayerAnimDataTable != nullptr, TEXT("AnimDataTable is not valid"));
	//UAnimSequence* Anim = PlayerAnimDataTable->FindRow<UAnimSequence>(TargetAnimName, 0);
	//ACharacter* Character = Cast<ACharacter>(GetOwner());


	
	
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
	NewPlayerCharacter->SetMoveMode(false);
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

void UBattleManagerComponent::DoBattleAction(FName ActionName, AMyCharacter* DeadPlayer)
{
	check(CurrentTurnCharacter);

	UBattleComponent* BattleComponent = CurrentTurnCharacter->FindComponentByClass<UBattleComponent>();
	check(BattleComponent);
	BattleComponent->DoAction(ActionName, DeadPlayer);
}

void UBattleManagerComponent::DoBattleActionWork()
{
	UBattleComponent* BattleComponent = CurrentTurnCharacter->FindComponentByClass<UBattleComponent>();
	check(BattleComponent);
	BattleComponent->DoActionWork();
}

void UBattleManagerComponent::InitBattle(AActor* BattleTile)
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, FString::Printf(TEXT("UBattleManagerComponent::InitBattle")));
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

	for (auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; ++Iter)
	{
		AMoveBoardPlayerController* PC = Cast<AMoveBoardPlayerController>(Iter->Get());
		check(PC);
		PC->MoveCamera(BattleMapArray[MapIndex]->GetNeutralSideCamera()->GetActorTransform());
	}
	
	CalculateTurn();
	
	for (FConstPlayerControllerIterator Iter = GetWorld()->GetPlayerControllerIterator();
		Iter; ++Iter)
	{
		AMoveBoardPlayerController* PC = CastChecked<AMoveBoardPlayerController>(Iter->Get());
		PC->SetBattleTurnArray(UseBattleTurnArray);
	}
	/*AMyGameModeBase* GameModeBase = Cast<AMyGameModeBase>(GetWorld()->GetAuthGameMode());
	checkf(GameModeBase != nullptr, TEXT("GameModeBase doesn't exist"));
	GameModeBase->GetTurnWidget()->GetBattleTurnWidget()->SetTurnArray(UseBattleTurnArray);*/
	

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

	//InitUnitTurn();// check whether first index of BattleTurnIndex is Enemy or not and StartUnitTurn;
	MoveToNextUnitTurn();
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

UDataTable* UBattleManagerComponent::GetPlayerAnimDataTable()
{
	return PlayerAnimDataTable;
}

void UBattleManagerComponent::SpawnEnemy_Implementation()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Purple, FString::Printf(TEXT("UBattleManagerComponent::SpawnEnemy")));
	int32 SpawnEnemyCount = 0;

	for (; SpawnEnemyCount < 3; ++SpawnEnemyCount)
	{
		if (SpawnEnemyCount + SpawnEnemyIndex >= EnemyClassArray.Num())
		{
			SpawnEnemyIndex += SpawnEnemyCount;
			return;
		}


		FTransform EnemySpawnTransform = BattleMapArray[MapIndex]->GetEnemySpawnPosition()[SpawnEnemyCount]->GetActorTransform();
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AMyCharacter* EnemyCharacter = GetWorld()->SpawnActor<AMyCharacter>(EnemyClassArray[SpawnEnemyCount + SpawnEnemyIndex], EnemySpawnTransform, SpawnParams);
		EnemyCharacter->SetMoveMode(false);
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Purple, FString::Printf(TEXT("World Name : %s"), *GetWorld()->GetName()));
		UBattleComponent* BattleComponent = Cast<UBattleComponent>(EnemyCharacter->GetComponentByClass(UBattleComponent::StaticClass()));
		UInventoryComponent* InventoryComponent = Cast<UInventoryComponent>(EnemyCharacter->GetComponentByClass(UInventoryComponent::StaticClass()));
		checkf(BattleComponent != nullptr, TEXT("EnemyCharacter has not BattleComponent"));
		checkf(InventoryComponent != nullptr, TEXT("EnemyCharacter has not InventoryComponent"));
		InventoryComponent->AddItem("NormalSword", 1); // Add Item to enemy to Drop Reward When Enemy die
		InventoryComponent->AddItem("NormalArmor", 1);
		//InventoryComponent->AddItem("God'sBeard", 1); can not found God's Beard in DataTable
		BattleComponent->SetBaseTransform(EnemySpawnTransform);
		BattleComponent->SetTargetCamera(BattleMapArray[MapIndex]->GetEnemySpawnPosition()[SpawnEnemyCount]->GetCameraPosition());
		checkf(EnemyCharacter != nullptr, TEXT("UBattleManagerComponent::SpawnEnemy : EnemyCharacter is not spawned"));
		EnemyCharacterArray.Add(EnemyCharacter);

		UE_LOG(LogTemp, Warning, TEXT("InventoryNum %d"), InventoryComponent->GetItemArray().Num());

	}
	
	SpawnEnemyIndex += SpawnEnemyCount + 1;
	return;
}

bool UBattleManagerComponent::TeleportCharacter()
{
	for (int i = 0; i < PlayerCharacterArray.Num(); ++i)
	{
		FTransform CharacterSpawnTransform = BattleMapArray[MapIndex]->GetPlayerSpawnPosition()[i]->GetActorTransform();
		PlayerCharacterArray[i]->SetActorTransform(CharacterSpawnTransform, false, nullptr, ETeleportType::TeleportPhysics);
		UBattleComponent* BattleComponent = Cast<UBattleComponent>(PlayerCharacterArray[i]->GetComponentByClass(UBattleComponent::StaticClass()));
		checkf(BattleComponent != nullptr, TEXT("PlayerCharacter has not BattleComponent"));
		BattleComponent->SetTargetCamera(BattleMapArray[MapIndex]->GetPlayerSpawnPosition()[i]->GetCameraPosition());
		BattleComponent->SetBaseTransform(CharacterSpawnTransform);
	}

	return true;
}

void UBattleManagerComponent::MoveLerpCamera_Implementation(FTransform TargetCameraTransform)
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, FString::Printf(TEXT("UBattleManagerComponent::MoveLerpCamera")));

	/* From : 
	APlayerController* LocalPlayerController = GEngine->GetFirstLocalPlayerController(GetWorld());
	APawn* LocalPawn = LocalPlay}erController->GetPawn();*/

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	APawn* Pawn = PC->GetPawn();
	
	TargetLocation = TargetCameraTransform.GetLocation();
	TargetRotation = TargetCameraTransform.GetRotation().Rotator();
	UE_LOG(LogTemp, Warning, TEXT("%s"), *TargetRotation.ToString());

	GetWorld()->GetTimerManager().ClearTimer(CameraLerpTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(CameraLerpTimerHandle, this, &UBattleManagerComponent::LerpTimerFunction, 0.01f, true);
}

void UBattleManagerComponent::LerpTimerFunction()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	APawn* Pawn = PC->GetPawn();

	Pawn->SetActorLocation(FMath::Lerp(Pawn->GetActorLocation(), TargetLocation, 0.01f));
	Pawn->FindComponentByClass<UCameraComponent>()->SetRelativeRotation(FMath::Lerp(Pawn->FindComponentByClass<UCameraComponent>()->GetRelativeRotation(), TargetRotation, 0.01f));
	
	if (Pawn->GetActorLocation() == TargetLocation)
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

//void UBattleManagerComponent::InitUnitTurn()
//{
//	return;
//
//	CurrentTurnCharacter = UseBattleTurnArray[0];
//	UBattleComponent* NewBattleComponent = Cast<UBattleComponent>(UseBattleTurnArray[0]->FindComponentByClass(UBattleComponent::StaticClass()));
//	if (NewBattleComponent->GetFactionType() == EFactionType::Player)
//	{
//		//checkf(UseBattleTurnArray[0] != nullptr, TEXT("UseBattleTurnArray is null"));
//
//		// From : BattleWidget->InitWidget(UseBattleTurnArray[0]);
//		for (auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; ++Iter)
//		{
//			AMoveBoardPlayerController* PC = Cast<AMoveBoardPlayerController>(Iter->Get());
//			check(PC);
//			if (UseBattleTurnArray[0]->GetControllerIndex() == GetWorld()->GetGameState<AMoveBoardGameState>()->GetControllerID(PC))
//			{
//				PC->InitBattleWidget(UseBattleTurnArray[0]);
//			}
//			else
//			{
//				PC->HideBattleWidget();
//			}
//		}
//
//		
//		UE_LOG(LogTemp, Warning, TEXT("%s Turn"), *UseBattleTurnArray[0]->GetName());
//	}
//	else if (NewBattleComponent->GetFactionType() == EFactionType::Enemy)
//	{
//		
//	
//		if (TargetPlayerArray.Num() != 0) // check if TargetPlayerArray is notempty
//		{
//
//		  int32 TargerCharacterNum = FMath::RandRange(0, TargetPlayerArray.Num() - 1); // Get Random Index In TargetCharacter Array
//		  UE_LOG(LogTemp, Warning, TEXT("%s  RandomEnemyAttack"), *UseBattleTurnArray[0]->GetName()); // enemyunit random attack
//		  NewBattleComponent->SetActionTarget(TargetPlayerArray[TargerCharacterNum]); // set ActionTarget At TargetCharacter Array
//		  NewBattleComponent->DoAction(); // Do RandomEnemyAttack
//		
//		}
//		else
//		{
//			UE_LOG(LogTemp, Warning, TEXT("Target is not exist"));
//		}
//	
//	}
//
//	UE_LOG(LogTemp, Warning, TEXT("TargetPlayer num %d"), TargetPlayerArray.Num());
//}

void UBattleManagerComponent::MoveToNextUnitTurn()
{
	UE_LOG(LogTemp, Warning, TEXT("UBattleManagerComponent::MoveToNextUnitTurn"));

	checkf(UseBattleTurnArray.Num() != 0, TEXT("UsebattleTurnArray is empty"));

	CurrentTurnCharacter = UseBattleTurnArray[0];

	UseBattleTurnArray.Add(CurrentTurnCharacter);
	UseBattleTurnArray.RemoveAt(0);

	if (CurrentTurnCharacter == nullptr)
	{
		CurrentTurnCharacter = UseBattleTurnArray[0];

		UseBattleTurnArray.Add(CurrentTurnCharacter);
		UseBattleTurnArray.RemoveAt(0);
		// Todo : Do Next Round
	}

	for (auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; ++Iter)
	{
		AMoveBoardPlayerController* PC = Cast<AMoveBoardPlayerController>(Iter->Get());
		check(PC);
		PC->AddUnitToImageArray(UseBattleTurnArray);
	}

	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("%s's Turn"), *CurrentTurnCharacter->GetName()));

	UBattleComponent* BattleComponent = CurrentTurnCharacter->FindComponentByClass<UBattleComponent>();
	check(BattleComponent);

	// Maybe to Fix it
	MoveLerpCamera(BattleComponent->GetTargetCamera()->GetActorTransform());
	
	if (BattleComponent->GetFactionType() == EFactionType::Player)
	{
		for (auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; ++Iter)
		{
			AMoveBoardPlayerController* PC = Cast<AMoveBoardPlayerController>(Iter->Get());
			check(PC);
			if (CurrentTurnCharacter->GetControllerIndex() == GetWorld()->GetGameState<AMoveBoardGameState>()->GetControllerID(PC))
			{
				PC->InitBattleWidget(CurrentTurnCharacter);
			}
			else
			{
				PC->HideBattleWidget();
			}
		}
	}
	else if (BattleComponent->GetFactionType() == EFactionType::Enemy)
	{
		if (TargetPlayerArray.Num() != 0) // check if TargetPlayerArray is notempty
		{
			int32 TargerCharacterNum = FMath::RandRange(0, TargetPlayerArray.Num() - 1);
			BattleComponent->SetActionTarget(TargetPlayerArray[TargerCharacterNum]);
			BattleComponent->DoAction();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Target is not exist"));
		}
	}	
}


void UBattleManagerComponent::RemoveDeadUnitFromArray(AMyCharacter* TargetCharacter)
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, FString::Printf(TEXT("UBattleManagerComponent::RemoveDeadUnitFromArray")));
	checkf(UseBattleTurnArray.Num() != 0, TEXT("UseBattleTurnArray is Empty"));

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
		UInventoryComponent* DeadEnemyInventoryComponent = Cast<UInventoryComponent>(TargetCharacter->FindComponentByClass(UInventoryComponent::StaticClass()));
		int32 RandomRewardNum = FMath::RandRange(0, DeadEnemyInventoryComponent->GetItemArray().Num()-1); // Get Random Index In ItemArray
		TArray<FItemInstance>RewardTempArray = DeadEnemyInventoryComponent->GetItemArray();
		RewardArray.Add(RewardTempArray[RandomRewardNum]);

		for (int i = 0; i < RewardArray.Num(); ++i)
		{
			UE_LOG(LogTemp, Warning, TEXT("ReWardArray %s"), *RewardArray[i].ItemRow.ToString());
		}
	
	}

	for (int i = 0; i < UseBattleTurnArray.Num();)
	{
		if (UseBattleTurnArray[i] == TargetCharacter)
		{
			//GameModeBase->GetTurnWidget()->GetBattleTurnWidget()->RemoveUnitFromImageArray(i); // Remove DeadUnitFrom Widget ImageArray
			UseBattleTurnArray.RemoveAt(i); // RemoveUnitFrom TurnArray
			for (auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; ++Iter)
			{
				AMoveBoardPlayerController* PC = Cast<AMoveBoardPlayerController>(Iter->Get());
				check(PC);
				PC->AddUnitToImageArray(UseBattleTurnArray);
			}
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

	checkf(UseBattleTurnArray.Num() != 0, TEXT("UseBattleTurnArray is Empty"));/*
	AMyGameModeBase* GameModeBase = Cast<AMyGameModeBase>(GetWorld()->GetAuthGameMode());
	checkf(GameModeBase != nullptr, TEXT("GameModeBase doesn't exist"));*/

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

	/*AMyGameModeBase* GameModeBase = Cast<AMyGameModeBase>(GetWorld()->GetAuthGameMode());
	checkf(GameModeBase != nullptr, TEXT("GameModeBase doesn't exist"));*/

	for (int32 i = 1; i < UseBattleTurnArray.Num(); ++i)
	{
		if (UseBattleTurnArray[i] == nullptr
			|| Cast<UStatusComponent>(UseBattleTurnArray[i]->FindComponentByClass(UStatusComponent::StaticClass()))->GetSpeed() < NewStatusComponent->GetSpeed())
		{
			UseBattleTurnArray.Insert(ResurrectCharacter, i); 
			checkf(UseBattleTurnArray.Num() != 0, TEXT("UsebattleTurnArray is empty"));
			// From : GameModeBase->GetTurnWidget()->GetBattleTurnWidget()->AddUnitToImageArray(UseBattleTurnArray);
			for (auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; ++Iter)
			{
				AMoveBoardPlayerController* PC = Cast<AMoveBoardPlayerController>(Iter->Get());
				check(PC);
				PC->AddUnitToImageArray(UseBattleTurnArray);
			}
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
			// From : GameModeBase->GetTurnWidget()->GetBattleTurnWidget()->AddUnitToImageArray(UseBattleTurnArray);
			for (auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; ++Iter)
			{
				AMoveBoardPlayerController* PC = Cast<AMoveBoardPlayerController>(Iter->Get());
				check(PC);
				PC->AddUnitToImageArray(UseBattleTurnArray);
			}
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
	
	// From : GameModeBase->GetTurnWidget()->DeleteHeartCount();
	for (auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; ++Iter)
	{
		AMoveBoardPlayerController* PC = Cast<AMoveBoardPlayerController>(Iter->Get());
		check(PC);
		PC->DeleteHeartCount();
	}

	DeadPlayerCount -= DeadPlayerCount;
	TargetPlayerArray.Add(ResurrectCharacter);
}

//void UBattleManagerComponent::CreateVictoryWidget()
//{
//	check(VictoryWidgetClass != nullptr);
//	VictoryWidget = CreateWidget<UVictoryWidget>(GetWorld()->GetFirstPlayerController(), VictoryWidgetClass);
//	check(VictoryWidget != nullptr)
//	VictoryWidget->InitWidget();
//	VictoryWidget->AddToPlayerScreen(0);
//	//for (int i = 0; i < RewardArray.Num(); ++i) // Add ItemList To VictoryWidget;
//	//{
//	//	UVictoryWidgetSlot* VictoryWidgetSlot = CreateWidget<UVictoryWidgetSlot>(GetWorld()->GetFirstPlayerController(), VictoryWidgetSlotClass);
//	//	VictoryWidgetSlot->SetItmeNameText(FText::FromName(RewardArray[i].ItemRow));
//	//	VictoryWidget->AddItemToItemListBox(VictoryWidgetSlot);
//	//}
//}

void UBattleManagerComponent::ReceiveReward()
{
	UE_LOG(LogTemp, Warning, TEXT("ReceiveReward Called"));

	if (UseBattleTurnArray[0] != nullptr)
	{
		
		UInventoryComponent* PlayerInventory = Cast<UInventoryComponent>(UseBattleTurnArray[0]->FindComponentByClass(UInventoryComponent::StaticClass()));
		
		if (RewardArray.Num() > 0)
		{
			PlayerInventory->AddItem(RewardArray[0].ItemRow, 1);
			RewardArray.RemoveAt(0);
			AMyCharacter* FirstIndexCharacter = UseBattleTurnArray[0];
			UseBattleTurnArray.Add(FirstIndexCharacter);
			UseBattleTurnArray.RemoveAt(0);
			for (int i = 0; i < PlayerInventory->GetItemArray().Num(); ++i)
			{
				UE_LOG(LogTemp, Warning, TEXT("ItemList: %s "), *PlayerInventory->GetItemInfoAtInventory(i)->ItemName.ToString());
			}
		}
		else if(RewardArray.Num()<=0)
		{
			MoveToNextStage();
		}
	}
	else
	{
	
		if (RewardArray.Num() > 0)
		{

			UseBattleTurnArray.Add(nullptr);
			UseBattleTurnArray.RemoveAt(0);
			UInventoryComponent* PlayerInventory = Cast<UInventoryComponent>(UseBattleTurnArray[0]->FindComponentByClass(UInventoryComponent::StaticClass()));
			PlayerInventory->AddItem(RewardArray[0].ItemRow, 1);
			RewardArray.RemoveAt(0);
			for (int i = 0; i < PlayerInventory->GetItemArray().Num(); ++i)
			{
				UE_LOG(LogTemp, Warning, TEXT("ItemList: %s "), *PlayerInventory->GetItemInfoAtInventory(i)->ItemName.ToString());
			}
		}
		else if (RewardArray.Num() <= 0)
		{
			MoveToNextStage();
		}
	}

}

AMyCharacter* UBattleManagerComponent::GetCurrentTurnCharacter() const
{
	return CurrentTurnCharacter;
}

void UBattleManagerComponent::EndBattle()
{
	++VictoryCount;
	
	UE_LOG(LogTemp, Warning, TEXT("Victory!!"));

	// From :
	/*BattleWidget->HideWidget();
	CreateVictoryWidget();*/
	for (auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; ++Iter)
	{
		AMoveBoardPlayerController* PC = Cast<AMoveBoardPlayerController>(Iter->Get());
		check(PC);
		PC->ChangeToVictoryWidget();
	}
}

void UBattleManagerComponent::MoveToNextStage()
{
	UE_LOG(LogTemp, Warning, TEXT("UBattleManagerComponent::MoveToNextStage"));
	BattleMapArray[MapIndex]->MoveNextSceneIndex();
	TeleportCharacter();
	SpawnEnemy();
	GetWorld()->GetTimerManager().ClearTimer(CameraLerpTimerHandle);
	
	for (auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; ++Iter)
	{
		AMoveBoardPlayerController* PC = Cast<AMoveBoardPlayerController>(Iter->Get());
		check(PC);
		PC->MoveCamera(BattleMapArray[MapIndex]->GetNeutralSideCamera()->GetActorTransform());
	}
}

void UBattleManagerComponent::GameOver()
{
	UE_LOG(LogTemp, Warning, TEXT("GameOver!!"));
}
