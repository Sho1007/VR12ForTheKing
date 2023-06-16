// Fill out your copyright notice in the Description page of Project Settings.


#include "../GameMode/SelectCharacterGameMode.h"

#include "GameFramework/PlayerState.h"

#include "../PlayerController/SelectCharacterPlayerController.h"
#include "../MyGameInstance.h"

void ASelectCharacterGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Cyan, FString::Printf(TEXT("SelectCharacter GameMode BeginPlay")));

	bUseSeamlessTravel = true;
	bActorSeamlessTraveled = true;
}

void ASelectCharacterGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (APlayerState* PlayerState = NewPlayer->GetPlayerState<APlayerState>())
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Cyan, FString::Printf(TEXT("%s : %d, %d"), *NewPlayer->Player->GetName(), PlayerState->GetPlayerId(), PlayerState->GetUniqueID()));
		}
	}

	ASelectCharacterPlayerController* PC = Cast<ASelectCharacterPlayerController>(NewPlayer);
	checkf(PC != nullptr, TEXT("PlayerController is not valid"));

	PC->SetPlayerIndex(PlayerControllerArray.Num());
	PlayerControllerArray.Add(PC);

	UMyGameInstance* GI = Cast<UMyGameInstance>(GetGameInstance());
	GI->AddPlayerController(PC);
}

void ASelectCharacterGameMode::HandleSeamlessTravelPlayer(AController*& C)
{
	Super::HandleSeamlessTravelPlayer(C);
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("ASelectCharacterGameMode::HandleSeamlessTravelPlayer")));
}