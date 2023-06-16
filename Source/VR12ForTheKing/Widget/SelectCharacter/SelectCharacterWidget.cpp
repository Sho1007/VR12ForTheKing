// Fill out your copyright notice in the Description page of Project Settings.


#include "../SelectCharacter/SelectCharacterWidget.h"

#include "SelectCharacterSlotWidget.h"
#include "../../PlayerController/SelectCharacterPlayerController.h"
#include "../../GameState/SelectCharacterGameState.h"

void USelectCharacterWidget::NativeConstruct()
{
	SelectCharacterSlotArray.Add(WBP_SelectCharacterSlot1);
	SelectCharacterSlotArray.Add(WBP_SelectCharacterSlot2);
	SelectCharacterSlotArray.Add(WBP_SelectCharacterSlot3);

	for (int i = 0; i < SelectCharacterSlotArray.Num(); ++i)
	{
		SelectCharacterSlotArray[i]->SetSlotIndex(i);
	}
}

void USelectCharacterWidget::UpdateWidget(TArray<FPlayerData>& PlayerDataArray)
{
	int32 LocalControllerIndex = Cast<ASelectCharacterPlayerController>(GetWorld()->GetFirstPlayerController())->GetPlayerIndex();
	for (int i = 0; i < PlayerDataArray.Num(); ++i)
	{
		// Select Part
		if (PlayerDataArray[i].ControllerIndex == -1)
		{
			SelectCharacterSlotArray[i]->Deselect();
		}
		else
		{
			if (PlayerDataArray[i].ControllerIndex == LocalControllerIndex)
			{
				SelectCharacterSlotArray[i]->Select();
			}
			else
			{
				SelectCharacterSlotArray[i]->Selected();
			}
		}

		// Ready Part
		SelectCharacterSlotArray[i]->Ready(PlayerDataArray[i].bIsReady);
	}
}