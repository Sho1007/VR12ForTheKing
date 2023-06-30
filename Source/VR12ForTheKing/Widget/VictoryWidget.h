// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VictoryWidget.generated.h"

/**
 * 
 */
class UVerticalBox;
class UTextBlock;
class UButton;
UCLASS()
class VR12FORTHEKING_API UVictoryWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UVictoryWidget(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable)
		void AddItemToItemListBox(UWidget* NewVictoryWidgetSlot);

	void InitWidget();

	UFUNCTION()
	void OnClickedReceiveButton();
private:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true, BindWidget))
	UVerticalBox* ItemListBox;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true, BindWidget))
	UButton* ReceiveItem;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true, BindWidget))
	UButton* Skip;

	UTextBlock* VictoryText;



};
