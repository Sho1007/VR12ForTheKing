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
	UFUNCTION(BlueprintNativeEvent)
	void UpdateMoveJudge(const TArray<bool>& SuccessArray);
	UFUNCTION(BlueprintNativeEvent)
	void HideMoveJudgeWidget();
	UFUNCTION(BlueprintCallable)
	void ShowEventWidget();
	UFUNCTION(BlueprintCallable)
	void InitEventWidget(const AEventActor* NewEventActor);
	UFUNCTION(BlueprintCallable)
	void HideEventWidget();
	UFUNCTION(BlueprintCallable)
	void ShowEventInfoWidget(FVector2D NewPos);
	UFUNCTION(BlueprintCallable)
	void HideEventInfoWidget();
	UFUNCTION(BlueprintCallable)
	void InitEventInfoWidget(const AEventActor* NewEventActor);

private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true, BindWidget))
	UEventWidget* WBP_Event;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true, BindWidget))
	UEventInfoWidget* WBP_EventInfo;
};