// Fill out your copyright notice in the Description page of Project Settings.

#include "../Widget/BattleWidget.h"

#include "Components/HorizontalBox.h"

#include "../Character/MyCharacter.h"
#include "../Component/BattleComponent.h"
#include "ActionWidget.h"
#include "../Event/TileEventManager.h"
#include "GameFramework/GameModeBase.h"
#include "Components/TextBlock.h"
#include "../Component/BattleManagerComponent.h"
#include "../MyGameModeBase.h"
#include "../Component//StatusComponent.h"
void UBattleWidget::HideWidget()
{
	this->SetVisibility(ESlateVisibility::Collapsed);
}

void UBattleWidget::ShowWidget()
{
	this->SetVisibility(ESlateVisibility::Visible);
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
	AMyGameModeBase* NewGamModeBase = Cast<AMyGameModeBase>(GetWorld()->GetAuthGameMode());
	UBattleManagerComponent* NewBattleManagerComponent =
		Cast<UBattleManagerComponent>(NewGamModeBase->FindComponentByClass(UBattleManagerComponent::StaticClass()));

	for (int32 i = 0; i < NewBattleManagerComponent->GetPlayerCharacterArrayNum(); ++i) // check whether there is deadcharacter, if deadcharacter exist create resurrection widget
	{
		if (NewBattleManagerComponent->GetPlayerCharacter(i) == NewTargetCharacter) continue;
		UStatusComponent* StatusComponent = Cast<UStatusComponent>(NewBattleManagerComponent->GetPlayerCharacter(i)->GetComponentByClass(UStatusComponent::StaticClass()));
		if (StatusComponent->IsDead() == true)
		{
			UActionWidget* ResurrectActionWidget = CreateWidget<UActionWidget>(GetWorld()->GetFirstPlayerController(), ActionWidgetClass);
			checkf(ResurrectActionWidget != nullptr, TEXT("ResurrectActionWidget is not created"));
			ResurrectActionWidget->InitWidget("Resurrection", this, BattleComponent, NewBattleManagerComponent->GetPlayerCharacter(i));
			HB_Action->AddChildToHorizontalBox(ResurrectActionWidget);
		}

	}
}

void UBattleWidget::InitActionDiscription(FName NewActionName)
{
	UTileEventManager* TileEventMangaer = Cast<UTileEventManager>(GetWorld()->GetAuthGameMode()->GetComponentByClass(UTileEventManager::StaticClass()));
	checkf(TileEventMangaer != nullptr, TEXT("GameMode doesn't have TileEventManager Component"));

	UDataTable* ActionDataTable = TileEventMangaer->GetActionDataTable();
	checkf(ActionDataTable != nullptr, TEXT("ActionDataTable is not valid"));
	FAction* NewAction = ActionDataTable->FindRow<FAction>(NewActionName, 0);
	checkf(NewAction != nullptr, TEXT("Cannot find NewAction"));

	TB_ActionName->SetText(NewAction->Name);

	checkf(ActionRangeTextArray.Num() > (int32)NewAction->ActionRange, TEXT("ActionRangeTextArray has not matched Text with NewAction's Range Type"));
	TB_AttackRange->SetText(ActionRangeTextArray[(int32)NewAction->ActionRange]);

	checkf(ActionTypeTextArray.Num() > (int32)NewAction->ActionType, TEXT("ActionTypeTextArray has not matched Text with NewAction's Type"));
	TB_AttackType->SetText(ActionTypeTextArray[(int32)NewAction->ActionType]);



	TB_Damage->SetText(FText::FromString(FString::Printf(TEXT("%d"), NewAction->Power)));
	TB_SlotAccuracy->SetText(FText::FromString(FString::Printf(TEXT("%d"), NewAction->CheckPercent)));
	TB_ActionDiscription->SetText(NewAction->Discription);


//	UChanceCoinSlot* NewChanceCoinSlot = CreateWidget<UChanceCoinSlot>(GetWorld()->GetFirstPlayerController(), ChanceCoinSlotClass);

}
