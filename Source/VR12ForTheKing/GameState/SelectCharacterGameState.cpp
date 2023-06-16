// Fill out your copyright notice in the Description page of Project Settings.


#include "../GameState/SelectCharacterGameState.h"

#include "../HUD/SelectCharacterHUD.h"


ASelectCharacterGameState::ASelectCharacterGameState()
{
	bReplicates = true;
	
}

void ASelectCharacterGameState::BeginPlay()
{
	PlayerDataArray.Init(FPlayerData(), 3);
}

void ASelectCharacterGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASelectCharacterGameState, PlayerDataArray);
}

void ASelectCharacterGameState::SetPlayer_Implementation(int32 SlotIndex, int32 PlayerIndex)
{
	checkf(SlotIndex < PlayerDataArray.Num() && 0 <= SlotIndex, TEXT("Invalid SlotIndex"));

	if (PlayerDataArray[SlotIndex].ControllerIndex != -1)
	{
		UE_LOG(LogTemp, Warning, TEXT("Slot is not empty"));
		return;
	}

	PlayerDataArray[SlotIndex].ControllerIndex = PlayerIndex;

	OnRep_PlayerDataArray();
}

void ASelectCharacterGameState::ResetPlayer_Implementation(int32 SlotIndex)
{
	checkf(SlotIndex < PlayerDataArray.Num() && 0 <= SlotIndex, TEXT("Invalid SlotIndex"));

	PlayerDataArray[SlotIndex].ControllerIndex = -1;
	PlayerDataArray[SlotIndex].bIsReady = false;

	OnRep_PlayerDataArray();
}

void ASelectCharacterGameState::ReadyPlayer(int32 SlotIndex, bool bIsReady)
{
	checkf(SlotIndex < PlayerDataArray.Num() && 0 <= SlotIndex, TEXT("Invalid SlotIndex"));

	PlayerDataArray[SlotIndex].bIsReady = bIsReady;

	OnRep_PlayerDataArray();

	if (CheckAllReady())
	{
		GetWorld()->ServerTravel("/Game/Maps/L_MoveBoard");
	}
}

bool ASelectCharacterGameState::GetReadyAt(int32 SlotIndex) const
{
	checkf(SlotIndex < PlayerDataArray.Num() && 0 <= SlotIndex, TEXT("Invalid SlotIndex"));

	return PlayerDataArray[SlotIndex].bIsReady;
}

bool ASelectCharacterGameState::CheckAllReady() const
{
	for (int i = 0; i < PlayerDataArray.Num(); ++i)
	{
		if (!PlayerDataArray[i].bIsReady) return false;
	}

	return true;
}

void ASelectCharacterGameState::OnRep_PlayerDataArray()
{
	if (UpdatePlayerData.IsBound())
	{
		UpdatePlayerData.Execute(PlayerDataArray);
	}
}