// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TileEventWidget.generated.h"

/**
 * 
 */
class UEventWidget;
class UEventInfoWidget;
class AEventActor;
UCLASS()
class VR12FORTHEKING_API UTileEventWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void InitEventWidget(const AEventActor* NewEventActor);
	UFUNCTION(BlueprintCallable)
	void ShowEventWidget();
	UFUNCTION(BlueprintCallable)
	void HideEventWidget();
	UFUNCTION(BlueprintCallable)
	void InitEventInfoWidget(const AEventActor* NewEventActor);
	UFUNCTION(BlueprintCallable)
	void ShowEventInfoWidget(FVector2D NewPos);
	UFUNCTION(BlueprintCallable)
	void HideEventInfoWidget();
	
	void HideWidget();
	
private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true, BindWidget))
	UEventWidget* WBP_TileEvent;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true, BindWidget))
	UEventInfoWidget* WBP_EventInfo;
};
