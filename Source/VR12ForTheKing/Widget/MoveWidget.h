// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MoveWidget.generated.h"

/**
 * 
 */
class UEventWidget;
class UEventInfoWidget;
class AEventActor;
UCLASS()
class VR12FORTHEKING_API UMoveWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void HideWidget();
	UFUNCTION(BlueprintNativeEvent)
	void UpdateMoveJudge(const TArray<bool>& SuccessArray);
	UFUNCTION(BlueprintNativeEvent)
	void HideMoveJudgeWidget();
};