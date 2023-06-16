// Fill out your copyright notice in the Description page of Project Settings.


#include "../HUD/SelectCharacterHUD.h"

#include "../Widget/SelectCharacter/SelectCharacterWidget.h"
#include "../GameState/SelectCharacterGameState.h"

void ASelectCharacterHUD::BeginPlay()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Cyan, FString::Printf(TEXT("SelectCharacter HUD BeginPlay")));
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Yellow, FString::Printf(TEXT("SelectCharacterWidget : %s"), SelectCharacterWidget != nullptr ? *SelectCharacterWidget->GetName() : *FString("Null")));

	checkf(SelectCharacterWidgetClass != nullptr, TEXT("SelectCharacter WidgetClass is not valid"));
	APlayerController* LocalPlayerController = GetWorld()->GetFirstPlayerController();
	if (LocalPlayerController)
	{
		SelectCharacterWidget = CreateWidget<USelectCharacterWidget>(LocalPlayerController, SelectCharacterWidgetClass, FName(TEXT("SelectCharacterWidget")));
		if (SelectCharacterWidget)
		{
			checkf(SelectCharacterWidget != nullptr, TEXT("SelectCharacter Widget is not created"));
			SelectCharacterWidget->AddToPlayerScreen(0);

			FInputModeUIOnly InputMode;
			InputMode.SetWidgetToFocus(SelectCharacterWidget->TakeWidget());
			LocalPlayerController->SetInputMode(InputMode);
			LocalPlayerController->SetShowMouseCursor(true);
		}

		ASelectCharacterGameState* GameState = Cast<ASelectCharacterGameState>(GetWorld()->GetGameState());
		if (GameState)
		{
			check(GameState != nullptr);
			GameState->UpdatePlayerData.BindUFunction(this, FName("UpdateSelectCharacterWidget"));
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, FString::Printf(TEXT("HUD : LocalPlayerController is null")));
	}
}

void ASelectCharacterHUD::UpdateSelectCharacterWidget(TArray<FPlayerData>& PlayerDataArray)
{
	SelectCharacterWidget->UpdateWidget(PlayerDataArray);
}