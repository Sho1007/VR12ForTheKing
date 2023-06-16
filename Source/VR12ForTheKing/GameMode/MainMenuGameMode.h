// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenuGameMode.generated.h"

/**
 * 
 */
UCLASS()
class VR12FORTHEKING_API AMainMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	void LoadMap();
};
