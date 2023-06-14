// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */

class AMyCharacter;
UCLASS()
class VR12FORTHEKING_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
	
private:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TArray<AMyCharacter*> CharacterArray;
};