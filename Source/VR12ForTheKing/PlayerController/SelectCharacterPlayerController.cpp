// Fill out your copyright notice in the Description page of Project Settings.


#include "../PlayerController/SelectCharacterPlayerController.h"

#include "GameFramework/PlayerState.h"
#include "GameFramework/HUD.h"

#include "../GameState/SelectCharacterGameState.h"
#include "../MyGameInstance.h"


ASelectCharacterPlayerController::ASelectCharacterPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bReplicates = true;
}

void ASelectCharacterPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Cyan, FString::Printf(TEXT("SelectCharacter PC BeginPlay")));

	if (HasAuthority())
	{
		if (UMyGameInstance* GI = GetGameInstance<UMyGameInstance>())
		{
			GI->AddPlayerController(this);
			if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Cyan, FString::Printf(TEXT("PlayerController Index : %d"), GI->FindPlayerControllerIndex(this)));
		}
	}
}

void ASelectCharacterPlayerController::ReadyPlayerAt_Implementation(int32 SlotIndex)
{
	ASelectCharacterGameState* GameState = Cast<ASelectCharacterGameState>(GetWorld()->GetGameState());
	checkf(GameState != nullptr, TEXT("GameState is not valid"));

	
	GameState->ReadyPlayer(SlotIndex, !GameState->GetReadyAt(SlotIndex));
}

void ASelectCharacterPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASelectCharacterPlayerController, PlayerIndex);
}

void ASelectCharacterPlayerController::SpawnDefaultHUD()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Yellow, FString::Printf(TEXT("ASelectCharacterPlayerController::SpawnDefaultHUD")));
	if (MyHUD) MyHUD->Destroy();
	Super::SpawnDefaultHUD();
}

void ASelectCharacterPlayerController::SetPlayerIndex(int32 NewPlayerIndex)
{
	PlayerIndex = NewPlayerIndex;

	OnRep_PlayerIndex();
}

int32 ASelectCharacterPlayerController::GetPlayerIndex() const
{
	return PlayerIndex;
}

void ASelectCharacterPlayerController::OnRep_PlayerIndex()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::Printf(TEXT("PlayerIndex : %d"), PlayerIndex));
	}
}

void ASelectCharacterPlayerController::SetPlayerAt_Implementation(int32 SlotIndex)
{
	ASelectCharacterGameState* GameState = Cast<ASelectCharacterGameState>(GetWorld()->GetGameState());
	checkf(GameState != nullptr, TEXT("GameState is not valid"));

	GameState->SetPlayer(SlotIndex, PlayerIndex);
}

void ASelectCharacterPlayerController::ResetPlayerAt_Implementation(int32 SlotIndex)
{
	ASelectCharacterGameState* GameState = Cast<ASelectCharacterGameState>(GetWorld()->GetGameState());
	checkf(GameState != nullptr, TEXT("GameState is not valid"));

	GameState->ResetPlayer(SlotIndex);
}