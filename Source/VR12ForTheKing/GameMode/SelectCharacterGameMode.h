// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SelectCharacterGameMode.generated.h"

/**
 * 
 */
class ASelectCharacterPlayerController;
UCLASS()
class VR12FORTHEKING_API ASelectCharacterGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	virtual void PostLogin(APlayerController* NewPlayer) override;

	virtual void HandleSeamlessTravelPlayer(AController*& C) override;

private:
	TArray<ASelectCharacterPlayerController*> PlayerControllerArray;
};
