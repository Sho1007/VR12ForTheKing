// Fill out your copyright notice in the Description page of Project Settings.

#include "../Widget/ActionWidget.h"

#include "Engine/DataTable.h"
#include "GameFramework/GameModeBase.h"
#include "Components/Button.h"

#include "../Event/TileEventManager.h"
#include "../Component/BattleComponent.h"
#include "BattleWidget.h"
#include "../Character/MyPlayerController.h"



void UActionWidget::InitWidget(FName NewActionName, UBattleWidget* NewParentWidget, UBattleComponent* NewBattleComponent, AMyCharacter* NewDeadPlayer)
{
	UTileEventManager* TileEventMangaer = Cast<UTileEventManager>(GetWorld()->GetAuthGameMode()->GetComponentByClass(UTileEventManager::StaticClass()));
	checkf(TileEventMangaer != nullptr, TEXT("GameMode doesn't have TileEventManager Component"));
	TargetBattleComponent = NewBattleComponent;
	if (NewDeadPlayer != nullptr)
	{
		DeadPlayer = NewDeadPlayer;
	}
	UDataTable* ActionDataTable = TileEventMangaer->GetActionDataTable();
	checkf(ActionDataTable != nullptr, TEXT("ActionDataTable is not valid"));
	ActionName = NewActionName;
	FAction* NewAction = ActionDataTable->FindRow<FAction>(ActionName, 0);
	checkf(NewAction != nullptr, TEXT("Cannot find NewAction"));
	Btn_Action->WidgetStyle.Normal.SetResourceObject(NewAction->Image);
	Btn_Action->OnClicked.AddDynamic(this, &UActionWidget::ActionButtonOnClicked);
	this->SetVisibility(ESlateVisibility::Visible);
	ParentWidget = NewParentWidget;
}

void UActionWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

FReply UActionWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s RightClicked"), *this->GetName());

		return FReply::Handled();
	}

	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

void UActionWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	UBattleWidget* BattleWidget = Cast<UBattleWidget>(ParentWidget);
	checkf(BattleWidget != nullptr, TEXT("ParentWidget is not UBattleWidget"));
	BattleWidget->InitActionDiscription(ActionName);
}

void UActionWidget::UseFocusToken()
{
	UE_LOG(LogTemp, Warning, TEXT("%s UseFocusToken"), *this->GetName());
}

AMyCharacter* UActionWidget::GetDeadPlayer()
{
	if (DeadPlayer != nullptr)
	{
		return DeadPlayer;
	}
	else
	{
		return 0;
	}
}

FName UActionWidget::GetActionName()
{
	return ActionName;
}

//when BattleComponenet action activated call function action ended in battlemangetcomponent
void UActionWidget::ActionButtonOnClicked()
{

	if (TargetBattleComponent->GetActionTarget() != nullptr) // check ActionTarget is nullpter, to check whether widget have to be hide or not
	{
		ParentWidget->HideWidget();
	}
	
	//this->SetVisibility(ESlateVisibility::Collapsed);
	TargetBattleComponent->DoAction(this);
	
}