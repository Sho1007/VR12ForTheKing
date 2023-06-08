// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StatusLayoutWidget.generated.h"

/**
 * 
 */
class AMyCharacter;
class UTextBlock;
class UStatusWidget;
class UWidgetSwitcher;
class UButton;
class UStatusDetailWidget;
class UInventoryWidget;
UCLASS()
class VR12FORTHEKING_API UStatusLayoutWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
public:
	void InitWidget(AMyCharacter* NewTargetCharacter);
	void UpdateWidget(AMyCharacter* NewTargetCharacter);
	void SwitchToStatus();
	void SwitchToInventory();
public:
	// Getter / Setter
	void SetParent(UStatusWidget* NewParentWidget);
	AMyCharacter* GetTargetCharacter() const;
	int32 GetActiveWidgetIndex() const;
	UFUNCTION()
	void SetStrengthText(int32 NewStrength);
	UFUNCTION()
	void SetVitalityText(int32 NewVitality);
	UFUNCTION()
	void SetIntelligenceText(int32 NewIntelligence);
	UFUNCTION()
	void SetCognitionText(int32 NewCognition);
	UFUNCTION()
	void SetTalentText(int32 NewTalent);
	UFUNCTION()
	void SetSpeedText(int32 NewSpeed);
	UFUNCTION()
	void SetLuckText(int32 NewLuck);
private:
	UFUNCTION()
	void CloseButtonOnClicked();
	
private:
	AMyCharacter* TargetCharacter;
	UStatusWidget* ParentWidget;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "Widget", meta = (AllowPrivateAccess = true, BindWidget))
	UButton* Btn_Close;
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "Widget", meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* TB_PlayerName;
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "Widget", meta = (AllowPrivateAccess = true, BindWidget))
	UWidgetSwitcher* WS_Layout;
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "Widget", meta = (AllowPrivateAccess = true, BindWidget))
	UStatusDetailWidget* WBP_StatusDetail;
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "Widget", meta = (AllowPrivateAccess = true, BindWidget))
	UInventoryWidget* WBP_Inventory;
	
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "Status", meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* TB_Strength;
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "Status", meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* TB_Vitality;
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "Status", meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* TB_Intelligence;
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "Status", meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* TB_Cognition;
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "Status", meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* TB_Talent;
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "Status", meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* TB_Speed;
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "Status", meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* TB_Luck;
};
