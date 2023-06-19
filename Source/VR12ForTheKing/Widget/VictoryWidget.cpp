// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/VictoryWidget.h"
#include"Components/VerticalBox.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "../MyGameModeBase.h"
#include "../Component/BattleManagerComponent.h"

void UVictoryWidget::AddItemToItemListBox(UWidget* NewVictoryWidgetSlot)
{
	
	ItemListBox->AddChildToVerticalBox(NewVictoryWidgetSlot);

}


void UVictoryWidget::InitWidget()
{
	ReceiveItem->OnClicked.AddDynamic(this, &UVictoryWidget::OnClickedReceiveButton);
}
void UVictoryWidget::OnClickedReceiveButton()
{
	UE_LOG(LogTemp, Warning, TEXT("ButtonClicked"));
	AMyGameModeBase* NewGameModeBase = Cast<AMyGameModeBase>(GetWorld()->GetAuthGameMode());
	UBattleManagerComponent* BattleManagerComponent = Cast<UBattleManagerComponent>(NewGameModeBase->FindComponentByClass(UBattleManagerComponent::StaticClass()));
	BattleManagerComponent->ReceiveReward();
	ItemListBox->RemoveChildAt(0);
}
