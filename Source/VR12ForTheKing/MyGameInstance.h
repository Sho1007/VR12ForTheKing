// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FCharacterData
{
	GENERATED_BODY()
	
public:
	void InitCharacterData(FColor NewColor, FName NewClass)
	{
		CharacterName = FText::FromString(TEXT("Player"));
		CharacterColor = NewColor;
		// Todo : Change Character Color To Widget
		CharacterClass = NewClass;
		// Todo : Spawn Character Test Actor with Class
	}
	
	FText CharacterName;
	FColor CharacterColor;
	FName CharacterClass;
};

class AMyCharacter;
UCLASS()
class VR12FORTHEKING_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	TArray<FCharacterData>& GetCharacterDataArray();

	void InitCharacterDataArray();

	void AddPlayerController(APlayerController* NewPlayerController);
	int32 FindPlayerControllerIndex(APlayerController* TargetPlayerController);
private:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TArray<FCharacterData> CharacterDataArray;

	TArray<APlayerController*> PlayerControlelrArray;
};