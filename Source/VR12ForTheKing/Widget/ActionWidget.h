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
class UBattleComponent;
UCLASS()
class VR12FORTHEKING_API UActionWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void InitWidget(FName NewActionName, UBattleWidget* NewParentWidget, UBattleComponent* NewBattleComponent);
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	void UseFocusToken();
private:
	UFUNCTION()
	void ActionButtonOnClicked();

	UBattleComponent* TargetBattleComponent;
	FName ActionName;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UButton* Btn_Action;
	UBattleWidget* ParentWidget;

	int32 FocusCount;

	bool bIsHovered;
};
