// Fill out your copyright notice in the Description page of Project Settings.


#include "../HexGrid/HexGridManager.h"

#include "../HexGrid/HexTile.h"

// Sets default values
UHexGridManager::UHexGridManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UHexGridManager::InitGirdInfo(TSubclassOf<AHexTile> NewHexTileClass, int32 NewWidth, int32 NewHeight, float NewXOffset, float NewXStartOffset, float NewYOffset)
{
	HexTileClass = NewHexTileClass;

	Width = NewWidth;
	Height = NewHeight;
	XOffset = NewXOffset;
	XStartOffset = NewXStartOffset;
	YOffset = NewYOffset;

	CreateGrid();
}

// Called when the game starts or when spawned
void UHexGridManager::BeginPlay()
{
	Super::BeginPlay();
}

void UHexGridManager::CreateGrid()
{
	// ! Warning : X, Y is Y, X in Unreal Coordinate
	
	FRotator SpawnRotation(0, 0, 0);
	for (int i = 0; i < Height; ++i)
	{
		SpawnLocation.Y = i % 2 == 0 ? 0 : -XStartOffset;
		HexGrid.Add(FTileRow());
		for (int j = 0; j < Width; ++j)
		{
			AHexTile* HexTile = GetWorld()->SpawnActor<AHexTile>(HexTileClass, SpawnLocation, SpawnRotation);
			//FAttachmentTransformRules AttachRules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepWorld, false);
			//HexTile->AttachToActor(this, AttachRules);
			HexTile->SetPos(FIntPoint(j, i));
			HexGrid[i].TileArray.Add(HexTile);
			SpawnLocation.Y -= XOffset;
		}
		SpawnLocation.X += YOffset;
	}
}

TArray<AHexTile*> UHexGridManager::GetPath()
{
	return CurrentPath;
}

AHexTile* UHexGridManager::GetNextPath()
{
	CurrentPathIndex++;
	//UE_LOG(LogTemp, Error, TEXT("CurrentPathIndex : %d"), CurrentPathIndex);
	if (CurrentPathIndex < CurrentPath.Num())
	{
		return CurrentPath[CurrentPathIndex];
	}
	
	return NULL;
}

AHexTile* UHexGridManager::GetTile(int X, int Y)
{
	return HexGrid[Y].TileArray[X];
}

void UHexGridManager::SetStartTile(AHexTile* NewStartTile)
{
	CurrentPathIndex = -1;
	//UE_LOG(LogTemp, Warning, TEXT("SetStartTile Called"));
	StartTile = NewStartTile;
	StartTile->ClickTile();
}

void UHexGridManager::SetEndTile(AHexTile* NewEndTile, int32 MovableCount)
{
	if (StartTile == NewEndTile || EndTile == NewEndTile || !NewEndTile) return;
	//UE_LOG(LogTemp, Warning, TEXT("SetEndTile Called"));

	EndTile = NewEndTile;
	
	TArray<AHexTile*> NewPath;
	FindPath(NewPath);
	if (NewPath.Num() > 0)
	{
		for (int i = 0; i < CurrentPath.Num(); ++i)
		{
			CurrentPath[i]->SetIsPath(false);
		}
		CurrentPath.Empty();
		int PathEndIndex = MovableCount + 1 < NewPath.Num() ? MovableCount + 1 : NewPath.Num();
		for (int i = 0; i < PathEndIndex; ++i)
		{
			CurrentPath.Add(NewPath[NewPath.Num() - 1 - i]);
		}
		for (int i = 0; i < CurrentPath.Num(); ++i)
		{
			CurrentPath[i]->SetIsPath(true, MovableCount - i);
		}
	}
}

void UHexGridManager::SpawnEnemy(FIntPoint Center)
{

}

void UHexGridManager::FindNeighborTiles(TArray<AHexTile*>& NewNeighborTileArray, AHexTile* CurrentTile, int32 distance)
{
	NewNeighborTileArray.Empty();
	FIntPoint CenterPos = CurrentTile->GetPos();
	for (int i = -distance; i <= distance; ++i)
	{
		for (int j = -distance; j <= distance; ++j)
		{
			if (CenterPos.Y + i < 0 || CenterPos.Y + i >= Height) continue;
			if (CenterPos.X + j < 0 || CenterPos.X + j >= Width) continue;
			if (FVector::Distance(CurrentTile->GetActorLocation(), HexGrid[CenterPos.Y + i].TileArray[CenterPos.X + j]->GetActorLocation()) <= distance * FindAdjOffset
				&& HexGrid[CenterPos.Y + i].TileArray[CenterPos.X + j]->GetIsPassable())
			{
				NewNeighborTileArray.Add(HexGrid[CenterPos.Y + i].TileArray[CenterPos.X + j]);
			}
		}
	}
}

void UHexGridManager::FindPath(TArray<AHexTile*>& OutArray)
{
	TArray<FTileNode> Open;
	TArray<bool> IsInOpen;
	TArray<bool> IsInClose;
	IsInOpen.Init(false, Width * Height);
	IsInClose.Init(false, Width * Height);

	StartTile->SetParentTile(NULL);
	EndTile->SetParentTile(NULL);

	Open.Add(FTileNode(StartTile, 0, FVector::Distance(StartTile->GetActorLocation(), EndTile->GetActorLocation())));

	IsInOpen[GetIndex(StartTile->GetPos())] = true;

	while (!Open.IsEmpty() && !EndTile->GetParentTile())
	{
		Open.Sort([](const FTileNode& A, const FTileNode& B)
			{
				return (A.G + A.H) < (B.G + B.H);
			});

		FTileNode Now = Open[0];
		Open.RemoveAt(0);
		IsInClose[GetIndex(Now.Tile->GetPos())] = true;

		// Get Adj Tiles
		TArray<AHexTile*> AdjArray;

		FindNeighborTiles(AdjArray, Now.Tile, 1);

		for (AHexTile* Iter : AdjArray)
		{
			if (Iter == EndTile)
			{
				EndTile->SetParentTile(Now.Tile);
				break;
			}
			if (IsInClose[GetIndex(Iter->GetPos())]) continue;

			if (IsInOpen[GetIndex(Iter->GetPos())])
			{
				for (FTileNode& TileNode : Open)
				{
					if (TileNode.Tile == Iter)
					{
						TileNode.G = FMath::Min(TileNode.G, Now.G + 1);
						break;
					}
				}
			}
			else
			{
				Iter->SetParentTile(Now.Tile);
				IsInOpen[GetIndex(Iter->GetPos())] = true;
				Open.Add(FTileNode(Iter, Now.G + 1, FVector::Distance(Iter->GetActorLocation(), EndTile->GetActorLocation())));
				//GEngine->AddOnScreenDebugMessage(-1, 6000, FColor::Cyan, FString::Printf(TEXT("Add : %d, %d"), Iter->GetPos().Y, Iter->GetPos().X));
			}
		}
		//GEngine->AddOnScreenDebugMessage(-1, 6000, FColor::Cyan, FString::Printf(TEXT("Adj %d, Open %d"), AdjArray.Num(), Open.Num()));
	}

	if (EndTile->GetParentTile())
	{
		AHexTile* Now = EndTile;
		while (Now)
		{
			OutArray.Add(Now);
			Now = Now->GetParentTile();
		}
	}
}

int UHexGridManager::GetIndex(FIntPoint Pos)
{
	return Pos.Y * Width + Pos.X;
}
