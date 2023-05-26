// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/DataTable.h"
#include "GameFramework/GameModeBase.h"
#include "Components/Button.h"

#include "../Widget/ActionWidget.h"
#include "../Event/TileEventManager.h"
#include "../Component/BattleComponent.h"
#include "BattleWidget.h"


void UActionWidget::InitWidget(FName NewActionName, UBattleWidget* NewParentWidget)
{
	UTileEventManager* TileEventMangaer = Cast<UTileEventManager>(GetWorld()->GetAuthGameMode()->GetComponentByClass(UTileEventManager::StaticClass()));
	checkf(TileEventMangaer != nullptr, TEXT("GameMode doesn't have TileEventManager Component"));

	UDataTable* ActionDataTable = TileEventMangaer->GetActionDataTable();
	checkf(ActionDataTable != nullptr, TEXT("ActionDataTable is not valid"));
	ActionName = NewActionName;
	FAction* NewAction = ActionDataTable->FindRow<FAction>(ActionName, 0);
	checkf(NewAction != nullptr, TEXT("Cannot find NewAction"));
	Btn_Action->WidgetStyle.Normal.SetResourceObject(NewAction->Image);

	Btn_Action->OnHovered.AddDynamic(this, &UActionWidget::ActionButtonOnHovered);

	ParentWidget = NewParentWidget;
}

void UActionWidget::ActionButtonOnHovered()
{
	//UE_LOG(LogTemp, Warning, TEXT("WidgetParent : %s"), *ParentWidget->GetName());
	UBattleWidget* BattleWidget = Cast<UBattleWidget>(ParentWidget);
	checkf(BattleWidget != nullptr, TEXT("ParentWidget is not UBattleWidget"));
	BattleWidget->InitActionDiscription(ActionName);
}