// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/ItemDetailWidget.h"

#include "GameFramework/GameModeBase.h"

#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/VerticalBox.h"

#include "../MyGameInstance.h"
#include "../Component/InventoryComponent.h"
#include "../Event/TileEventManager.h"
#include "../Component/BattleComponent.h"

void UItemDetailWidget::InitWidget(FItem* NewItemInfo)
{
	TB_ItemName->SetText(NewItemInfo->ItemName);

	switch (NewItemInfo->ItemRarity)
	{
	case EItemRarity::COMMON:
		TB_ItemRank->SetText(FText::FromString(FString(TEXT("일반"))));
		Brd_ItemImage->SetBrushColor(FLinearColor::White);
		Brd_ItemDiscription->SetBrushColor(FLinearColor::White);
		break;
	case EItemRarity::UNCOMMON:
		TB_ItemRank->SetText(FText::FromString(FString(TEXT("언커먼"))));
		Brd_ItemImage->SetBrushColor(FLinearColor::Green);
		Brd_ItemDiscription->SetBrushColor(FLinearColor::Green);
		break;
	case EItemRarity::RARE:
		TB_ItemRank->SetText(FText::FromString(FString(TEXT("희귀"))));
		Brd_ItemImage->SetBrushColor(FLinearColor::Blue);
		Brd_ItemDiscription->SetBrushColor(FLinearColor::Blue);
		break;
	case EItemRarity::ARTIFACT:
		TB_ItemRank->SetText(FText::FromString(FString(TEXT("전설"))));
		Brd_ItemImage->SetBrushColor(FLinearColor::Red);
		Brd_ItemDiscription->SetBrushColor(FLinearColor::Red);
		break;
	}

	if (NewItemInfo->ItemType == EItemType::EQUIPMENT && NewItemInfo->EquipmentType == EEquipmentType::WEAPON)
	{
		VB_WeaponDiscription->SetVisibility(ESlateVisibility::HitTestInvisible);

		FName ActionRow = NewItemInfo->ActionArray[0];
		FAction* ActionInfo = GetGameInstance<UMyGameInstance>()->FindAction(ActionRow);

		checkf(ActionInfo != nullptr, TEXT("ActionInfo is nullptr"));

		TB_Damage->SetText(FText::FromString(FString::FromInt(ActionInfo->Power)));
	}
	else
	{
		VB_WeaponDiscription->SetVisibility(ESlateVisibility::Collapsed);
	}
	
	Img_ItemIcon->SetBrushFromTexture(NewItemInfo->ItemIcon);

	TB_ItemDiscription->SetText(FText::FromString(NewItemInfo->ItemDiscription));
}