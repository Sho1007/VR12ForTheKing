// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

TArray<FCharacterData>& UMyGameInstance::GetCharacterDataArray()
{
	// TODO: insert return statement here

	return CharacterDataArray;
}

void UMyGameInstance::InitCharacterDataArray()
{
	CharacterDataArray.Empty();
	CharacterDataArray.Init(FCharacterData(), 3);
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