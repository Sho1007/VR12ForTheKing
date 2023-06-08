// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StatusWidget.generated.h"

/**
 * 
 */
struct FItem;

class UStatusLayoutWidget;
class UStatusBoardWidget;
class UItemDetailWidget;
class UItemSelectMenuWidget;
class UEquipSelectMenuWidget;
class UStatusComponent;
class AMyCharacter;
UCLASS()
class VR12FORTHEKING_API UStatusWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	bool UpdateStatusBoard(int BoardIndex);
	void HideWidget();
	void OpenInventory(AMyCharacter* TargetCharacter);
	void OpenStatus(AMyCharacter* TargetCharacter);

	void UpdateLayoutWidget(AMyCharacter* NewTargetCharacter);

public:
	UFUNCTION()
	void UpdateStrength(UStatusBoardWidget* TargetBoard, int32 Strength);
	UFUNCTION()
	void UpdateVitality(UStatusBoardWidget* TargetBoard, int32 Vitality);
	UFUNCTION()
	void UpdateIntelligence(UStatusBoardWidget* TargetBoard, int32 Intelligence);
	UFUNCTION()
	void UpdateCognition(UStatusBoardWidget* TargetBoard, int32 Cognition);
	UFUNCTION()
	void UpdateTalent(UStatusBoardWidget* TargetBoard, int32 Talent);
	UFUNCTION()
	void UpdateSpeed(UStatusBoardWidget* TargetBoard, int32 Speed);
	UFUNCTION()
	void UpdateLuck(UStatusBoardWidget* TargetBoard, int32 Luck);

public:
	// Getter / Setter
	void SetParentToChild();

	void SetOwnerCharacter(const TArray<AMyCharacter*>& NewCharacterArray);

	void InitItemDetail(FItem* NewItemInfo);
	void HideItemDetail();

	void InitItemSelectMenu(AMyCharacter* OwnerCharacter, int32 ItemIndex);
	
	void InitEquipSelectMenu(AMyCharacter* OwnerCharacter, int32 SlotIndex);
	
private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget, AllowPrivateAccess = true))
	UStatusBoardWidget* WBP_StatusBoard1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget, AllowPrivateAccess = true))
	UStatusBoardWidget* WBP_StatusBoard2;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget, AllowPrivateAccess = true))
	UStatusBoardWidget* WBP_StatusBoard3;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget, AllowPrivateAccess = true))
	UStatusLayoutWidget* WBP_StatusLayout;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget, AllowPrivateAccess = true))
	UItemDetailWidget* WBP_ItemDetail;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget, AllowPrivateAccess = true))
	UItemSelectMenuWidget* WBP_ItemSelectMenu;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget, AllowPrivateAccess = true))
	UEquipSelectMenuWidget* WBP_EquipSelectMenu;
};