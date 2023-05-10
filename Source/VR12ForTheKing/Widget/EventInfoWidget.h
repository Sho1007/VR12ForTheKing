// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EventInfoWidget.generated.h"

/**
 * 
 */
class AEventActor;
class UTextBlock;
class UBorder;
UCLASS()
class VR12FORTHEKING_API UEventInfoWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Init(AEventActor* NewEventActor);

private:
	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* TB_EventName;
	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* TB_Discription1;
	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget))
	UBorder* Border_MonsterLevel;
	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget))
	UBorder* Border_MonsterCount;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	FSlateColor EnemyDiscriptionColor;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	FSlateColor NormalDiscriptionColor;
};
