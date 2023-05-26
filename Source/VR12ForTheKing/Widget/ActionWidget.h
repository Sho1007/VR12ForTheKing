// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ActionWidget.generated.h"

/**
 * 
 */
class UButton;
class UBattleWidget;
UCLASS()
class VR12FORTHEKING_API UActionWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void InitWidget(FName NewActionName, UBattleWidget* NewParentWidget);
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void UseFocusToken();
private:
	UFUNCTION()
	void ActionButtonOnHovered();
	UFUNCTION()
	void ActionButtonOnClicked();
	UFUNCTION()
	void ActionButtonOnUnhovered();
	FName ActionName;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UButton* Btn_Action;
	UBattleWidget* ParentWidget;

	int32 FocusCount;

	bool bIsHovered;
};
