// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"

#include "HexGrid/HexGridManager.h"
#include "HexGrid/HexTile.h"
#include "Character/MyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Character/MyPlayerController.h"
#include "AIController.h"

void AMyGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	PrimaryActorTick.bCanEverTick = false;

	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(this, HexGridManagerClass, OutActors);
	if (OutActors.Num() > 0)
	{
		HexGridManager = CastChecked<AHexGridManager>(OutActors[0]);
	}

	if (HexGridManager)
	{
		HexGridManager->CreateGrid();
		CreatePlayer();
	}

	MoveJudgeArray.Init(true, 5);
	NextTile = NULL;

	DoNextTurn();
}

void AMyGameModeBase::SetStartTile(AHexTile* NewStartTile)
{
	HexGridManager->SetStartTile(NewStartTile);
}

void AMyGameModeBase::SetEndTile(AHexTile* NewEndTile)
{
	HexGridManager->SetEndTile(NewEndTile, CurrentMovableCount);
}

void AMyGameModeBase::CheckMoveCount()
{
	CurrentMovableCount = 2;
	for (int i = 2; i < 5; ++i)
	{
		MoveJudgeArray[i] = UKismetMathLibrary::RandomBoolWithWeight(0.5f);
		if (MoveJudgeArray[i])
		{
			CurrentMovableCount++;
		}
	}
}

void AMyGameModeBase::MoveCharacter()
{
	bIsMoved = true;
	GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Yellow, FString::Printf(TEXT("MoveCharacter Called")));
	NextTile = HexGridManager->GetNextPath();
	if (NextTile)
	{
		UE_LOG(LogTemp, Error, TEXT("NextTile : %s"), *NextTile->GetPos().ToString());
		CurrentCharacter->SetDestination(NextTile->GetActorLocation());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("NextTile is NULL"));
		// NextTile == NULL 목적지에 도착함
		DoNextTurn();
	}
	
}

void AMyGameModeBase::ReachToTile()
{
	UE_LOG(LogTemp, Error, TEXT("ReachToTile is Called"));

	if (NextTile)
	{
		UE_LOG(LogTemp, Error, TEXT("NextTile : %s"), *NextTile->GetPos().ToString());
		NextTile->SetIsPath(false);
		CurrentCharacter->SetCurrentTile(NextTile);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 60, FColor::Red, FString::Printf(TEXT("NextTile is NULL")));
	}
	
	// Todo : Random Encounter
	MoveCharacter();
}

const AMyPlayerController* AMyGameModeBase::GetCurrentPlayer() const
{
	return CurrentPlayer;
}

const bool AMyGameModeBase::GetIsMoved() const
{
	return bIsMoved;
}

void AMyGameModeBase::CreatePlayer()
{
	if (CharacterClass)
	{
		FVector SpawnLocation(0, 0, 100);
		for (int i = 0; i < 3; ++i)
		{
			
			AMyCharacter* MyCharacter = GetWorld()->SpawnActor<AMyCharacter>(CharacterClass, SpawnLocation, FRotator(0, 0, 0));
			MyCharacter->Init(this);
			MyCharacter->SetCurrentTile(HexGridManager->GetTile(0,0));
			CharacterArray.Add(MyCharacter);
			GEngine->AddOnScreenDebugMessage(-1, 60, FColor::Yellow, FString::Printf(TEXT("CharacterArray Num : %d"), CharacterArray.Num()));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("MyGameModeBase:: CharacterClass is not valid"));
	}
	int32 PlayerNum = UGameplayStatics::GetNumPlayerControllers(this);
	for (int i = 0; i < PlayerNum; ++i)
	{
		PlayerControllerArray.Add(Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(this, i)));
	}
}

void AMyGameModeBase::DoNextTurn()
{
	if (CharacterArray.Num())
	{
		bIsMoved = false;
		CurrentTurn++;
		CurrentCharacter = CharacterArray[(CurrentTurn - 1) % CharacterArray.Num()];
		CurrentPlayer = PlayerControllerArray[(CurrentTurn - 1) % PlayerControllerArray.Num()];
		UE_LOG(LogTemp, Warning, TEXT("CurrentCharacter : %s , CurrentPlayerController : %s"), *CurrentCharacter->GetName(), *CurrentPlayer->GetName());
		// 카메라 이동
		// // 시작 바닥 설정
		HexGridManager->SetStartTile(CurrentCharacter->GetCurrentTile());
		// 이동 확률 체크
		CheckMoveCount();
		// 이동 -> 이동은 Widget Animation 끝나고
	}
}
