// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../VR12ForTheKing.h"
#include "Blueprint/UserWidget.h"
#include "EventActionButtonWidget.generated.h"

/**
 * 
 */

class UButton;
class UTextBlock;
UCLASS()
class VR12FORTHEKING_API UEventActionButtonWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void ActionButtonOnClicked();

	void SetButtonName(FText NewButtonName);
	void SetButtonType(ETileEventActionType NewButtonType);

protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly,meta = (BindWidget))
	UButton* Btn_Action;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (BindWidget))
	UTextBlock* TB_ActionName;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	ETileEventActionType TileEventActionType;
};