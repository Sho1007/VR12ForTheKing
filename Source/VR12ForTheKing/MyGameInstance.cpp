// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

#include "Kismet/GameplayStatics.h"
#include "Item/ItemBase.h"
#include "Component/BattleComponent.h"

UMyGameInstance::UMyGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("UMyGameInstance::UMyGameInstance"));
}

void UMyGameInstance::Init()
{
	Super::Init();
	
	UE_LOG(LogTemp, Warning, TEXT("UMyGameInstance::Init"));
}

void UMyGameInstance::AddPlayerController(APlayerController* NewPlayerController)
{
	if (FindPlayerControllerIndex(NewPlayerController) == INDEX_NONE)
	{
		PlayerControlelrArray.Add(NewPlayerController);
	}
	else
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Yellow, FString::Printf(TEXT("UMyGameInstance::AddPlayerController : Already in Array")));
	}
}

int32 UMyGameInstance::FindPlayerControllerIndex(APlayerController* TargetPlayerController)
{
	for (int i = 0; i < PlayerControlelrArray.Num(); ++i)
	{
		if (PlayerControlelrArray[i]->Player == TargetPlayerController->Player)
		{
			return i;
		}
	}

	return INDEX_NONE;
}

void UMyGameInstance::PlaySound2D(FName SoundName)
{
	if (!SoundDataTable)
	{
		UE_LOG(LogTemp, Log, TEXT("UMyGameInstance::PlaySound2D : Sound DataTable is not valid"));
		return;
	}
	if (SoundName.IsNone())
	{
		UE_LOG(LogTemp, Log, TEXT("UMyGameInstance::PlaySound2D : SoundName is None"));
		return;
	}

	FSoundData* SoundData = SoundDataTable->FindRow<FSoundData>(SoundName, FString(""));
	if (SoundData)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), SoundData->SoundAsset);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("UMyGameInstance::PlaySound2D : Cannot Find Sound Name In DataTable"));
	}
}

FItem* UMyGameInstance::FindItem(FName ItemRow)
{
	if (ItemRow.IsNone()) return nullptr;
	return ItemDataTable->FindRow<FItem>(ItemRow, FString(""));
}

FAction* UMyGameInstance::FindAction(FName ActionRow)
{
	if (ActionRow.IsNone()) return nullptr;
	return ActionDataTable->FindRow<FAction>(ActionRow, FString(""));
}