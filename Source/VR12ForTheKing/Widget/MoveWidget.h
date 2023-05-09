// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MoveWidget.generated.h"

/**
 * 
 */
class UEventWidget;
UCLASS()
class VR12FORTHEKING_API UMoveWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent)
	void UpdateMoveJudge(const TArray<bool>& SuccessArray);
	UFUNCTION(BlueprintNativeEvent)
	void HideMoveJudgeWidget();
	UFUNCTION(BlueprintCallable)
	void HideEventWidget();

private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true, BindWidget))
	UEventWidget* WBP_Event;
};