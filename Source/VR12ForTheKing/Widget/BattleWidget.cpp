// Fill out your copyright notice in the Description page of Project Settings.

#include "../Widget/BattleWidget.h"

#include "Components/HorizontalBox.h"
#include "Kismet/GameplayStatics.h"

#include "../MyGameInstance.h"
#include "../Character/MyCharacter.h"
#include "../Component/BattleComponent.h"
#include "ActionWidget.h"
#include "../Event/TileEventManager.h"
#include "GameFramework/GameModeBase.h"
#include "Components/TextBlock.h"
#include "../Component/BattleManagerComponent.h"
//#include "../MyGameModeBase.h"
#include "../Component/StatusComponent.h"
#include "ChanceCoinSlot.h"
#include "Components/Overlay.h"
#include "../Widget/VictoryWidget.h"
#include "../GameState/MoveBoardGameState.h"
void UBattleWidget::HideWidget()
{
	this->HB_Action->SetVisibility(ESlateVisibility::Hidden);
	this->DiscriptionOverlay->SetVisibility(ESlateVisibility::Hidden);
	//this->SetVisibility(ESlateVisibility::Collapsed);
}

void UBattleWidget::ShowWidget()
{
	//this->SetVisibility(ESlateVisibility::Visible);
	this->HB_Action->SetVisibility(ESlateVisibility::Visible);
	this->DiscriptionOverlay->SetVisibility(ESlateVisibility::Visible);
}

void UBattleWidget::InitWidget(AMyCharacter* NewTargetCharacter)
{
	//UE_LOG(LogTemp, Warning, TEXT("%s Turn"), *NewTargetCharacter->GetName());
	HB_Action->ClearChildren();
	TargetCharacter = NewTargetCharacter;
	UBattleComponent* BattleComponent = Cast<UBattleComponent>(NewTargetCharacter->GetComponentByClass(UBattleComponent::StaticClass()));
	checkf(BattleComponent != nullptr, TEXT("Character has no Battle Component"));

	checkf(ActionWidgetClass != nullptr, TEXT("ActionWidgetClass is not valid"));
	TArray<FName> ActionArray = BattleComponent->GetActionArray();
	for (int32 i = 0; i < ActionArray.Num(); ++i)
	{
		UActionWidget* ActionWidget = CreateWidget<UActionWidget>(GetWorld()->GetFirstPlayerController(), ActionWidgetClass);

		checkf(ActionWidget != nullptr, TEXT("ActionWidget is not created"));
		ActionWidget->InitWidget(ActionArray[i], this, BattleComponent);
		HB_Action->AddChildToHorizontalBox(ActionWidget);
	}

	


	/*AMyGameModeBase* NewGamModeBase = Cast<AMyGameModeBase>(GetWorld()->GetAuthGameMode());
	UBattleManagerComponent* NewBattleManagerComponent =
		Cast<UBattleManagerComponent>(NewGamModeBase->FindComponentByClass(UBattleManagerComponent::StaticClass()));*/

	AMoveBoardGameState* GameState = GetWorld()->GetGameState<AMoveBoardGameState>();
	check(GameState);
	// Todo : Modify Resurrect Function To MultiPlayer 
	//for (int32 i = 0; i < NewBattleManagerComponent->GetPlayerCharacterArrayNum(); ++i) // check whether there is deadcharacter, if deadcharacter exist create resurrection widget
	//{
	//	if (NewBattleManagerComponent->GetPlayerCharacter(i) == NewTargetCharacter) continue;
	//	UStatusComponent* StatusComponent = Cast<UStatusComponent>(NewBattleManagerComponent->GetPlayerCharacter(i)->GetComponentByClass(UStatusComponent::StaticClass()));
	//	if (StatusComponent->IsDead() == true)
	//	{
	//		UActionWidget* ResurrectActionWidget = CreateWidget<UActionWidget>(GetWorld()->GetFirstPlayerController(), ActionWidgetClass);	
	//		checkf(ResurrectActionWidget != nullptr, TEXT("ResurrectActionWidget is not created"));
	//		ResurrectActionWidget->InitWidget("Resurrection", this, BattleComponent, NewBattleManagerComponent->GetPlayerCharacter(i));
	//		HB_Action->AddChildToHorizontalBox(ResurrectActionWidget);
	//	}
	//}

	ShowWidget();
	WBP_VictoryWidget->InitWidget();
	WBP_VictoryWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void UBattleWidget::InitActionDiscription(FName NewActionName)
{
	/* Todo : 
	UTileEventManager* TileEventMangaer = Cast<UTileEventManager>(GetWorld()->GetAuthGameMode()->GetComponentByClass(UTileEventManager::StaticClass()));
	checkf(TileEventMangaer != nullptr, TEXT("GameMode doesn't have TileEventManager Component"));

	UDataTable* ActionDataTable = TileEventMangaer->GetActionDataTable();
	checkf(ActionDataTable != nullptr, TEXT("ActionDataTable is not valid"));

	PlayerAction = ActionDataTable->FindRow<FAction>(NewActionName, 0);
	*/

	PlayerActionName = NewActionName;
	AMoveBoardGameState* GameState = GetWorld()->GetGameState<AMoveBoardGameState>();
	check(GameState);
	PlayerAction = GameState->GetBattleAction(PlayerActionName);
	checkf(PlayerAction != nullptr, TEXT("Cannot find NewAction"));

	TB_ActionName->SetText(PlayerAction->Name);

	checkf(ActionRangeTextArray.Num() > (int32)PlayerAction->ActionRange, TEXT("ActionRangeTextArray has not matched Text with NewAction's Range Type"));
	TB_AttackRange->SetText(ActionRangeTextArray[(int32)PlayerAction->ActionRange]);

	checkf(ActionTypeTextArray.Num() > (int32)PlayerAction->ActionType, TEXT("ActionTypeTextArray has not matched Text with NewAction's Type"));
	TB_AttackType->SetText(ActionTypeTextArray[(int32)PlayerAction->ActionType]);

	TB_Damage->SetText(FText::FromString(FString::Printf(TEXT("%d"), PlayerAction->Power)));
	TB_SlotAccuracy->SetText(FText::FromString(FString::Printf(TEXT("%d"), PlayerAction->CheckPercent)));
	TB_ActionDiscription->SetText(PlayerAction->Discription);

	InitChanceCoinBox(PlayerAction->CheckCount, PlayerAction->StatType);
}

void UBattleWidget::StartUpdateChanceSlot(int32 CoinSize, EStatusType StatusType, TArray<bool> NewChanceArray)
{
	InitChanceCoinBox(CoinSize, StatusType);
	TargetChanceArray = NewChanceArray;
	ChanceCoinBoxIndex = 0;
	GetWorld()->GetTimerManager().SetTimer(CoinCheckTimerHandle, this, &UBattleWidget::CoinTimerFunction, 0.5f, true);
	
}

void UBattleWidget::InitChanceCoinBox(int32 CoinSize, EStatusType StatusType)
{
	check(CoinChanceBox);
	if (CoinChanceBox != nullptr)
	{
		CoinChanceBox->ClearChildren();
		CoinChanceBox->SetVisibility(ESlateVisibility::Visible);
	}

	for (int i = 0; i < CoinSize; ++i) // Add Chance Slot amount of CheckCount
	{
		UChanceCoinSlot* NewChanceCoinSlot = CreateWidget<UChanceCoinSlot>(GetWorld()->GetFirstPlayerController(), ChanceCoinSlotClass);// create ChanceCoinSlot Widget
		NewChanceCoinSlot->SetSwitchCoinImage(0);
		CoinChanceBox->AddChildToHorizontalBox(NewChanceCoinSlot);

		if (StatusType == EStatusType::Strength)
		{
			CoinTexture = NewChanceCoinSlot->GetCoinImageFromArray(0);
		}
		else if (StatusType == EStatusType::Focus)
		{
			CoinTexture = NewChanceCoinSlot->GetCoinImageFromArray(1);
		}
		else if (StatusType == EStatusType::Intelligence)
		{
			CoinTexture = NewChanceCoinSlot->GetCoinImageFromArray(2);
		}

		if (CoinTexture != nullptr)
		{
			NewChanceCoinSlot->SetImage(CoinTexture);
		}

	}

	UChanceCoinSlot* LastChanceCoinSlot = CreateWidget<UChanceCoinSlot>(GetWorld()->GetFirstPlayerController(), ChanceCoinSlotClass);// create ChanceCoinSlot Widget
	LastChanceCoinSlot->SetVisibility(ESlateVisibility::Collapsed);
	CoinChanceBox->AddChildToHorizontalBox(LastChanceCoinSlot);
}

void UBattleWidget::ChangeToVictoryWidget()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Magenta, FString::Printf(TEXT("UBattleWidget::ChangeToVictoryWidget")));
	HB_Action->SetVisibility(ESlateVisibility::Collapsed);
	CoinChanceBox->SetVisibility(ESlateVisibility::Collapsed);
	DiscriptionOverlay->SetVisibility(ESlateVisibility::Collapsed);

	WBP_VictoryWidget->SetVisibility(ESlateVisibility::Visible);
}

void UBattleWidget::CoinTimerFunction()
{
	
	UChanceCoinSlot* NewChanceCoinSlot = Cast<UChanceCoinSlot>(CoinChanceBox->GetChildAt(ChanceCoinBoxIndex));

	if (TargetChanceArray[ChanceCoinBoxIndex] == true)
	{
		UE_LOG(LogTemp, Warning, TEXT("Success"));
	    NewChanceCoinSlot->SetSwitchCoinImage(1);
		GetGameInstance<UMyGameInstance>()->PlaySound2D("ChanceCheckSuccessed");
		
	}
	else if(TargetChanceArray[ChanceCoinBoxIndex] == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("Fail"));
		NewChanceCoinSlot->SetSwitchCoinImage(2);
		if (ChanceCoinBoxIndex < CoinChanceBox->GetChildrenCount()-1)
		{
			GetGameInstance<UMyGameInstance>()->PlaySound2D("ChanceCheckFailed");
		}
	}
	
	ChanceCoinBoxIndex++;
	if (ChanceCoinBoxIndex >= CoinChanceBox->GetChildrenCount())
	{
		GetWorld()->GetTimerManager().ClearTimer(CoinCheckTimerHandle);
		CoinChanceBox->SetVisibility(ESlateVisibility::Hidden);
		if (GetOwningPlayer()->HasAuthority())
		{
			/* From : 
			UBattleComponent* NewBattleComponent = Cast<UBattleComponent>(TargetCharacter->FindComponentByClass(UBattleComponent::StaticClass()));
			NewBattleComponent->DoActionWork(PlayerActionName);*/
			AMoveBoardGameState* GameState = GetWorld()->GetGameState<AMoveBoardGameState>();
			check(GameState);
			GameState->DoBattleActionWork();
		}
		ChanceCoinBoxIndex = 0;
	}
}




