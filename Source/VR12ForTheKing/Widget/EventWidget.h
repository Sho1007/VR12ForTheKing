// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EventWidget.generated.h"

/**
 * 
 */
class AEventActor;
class UTextBlock;
class UBorder;
class UUniformGridPanel;
class UEventActionButtonWidget;
UCLASS()
class VR12FORTHEKING_API UEventWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void InitWidget(const AEventActor* NewEventActor);

private:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* Txt_EventName;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* Txt_Discription1;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* Txt_Discription2;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UUniformGridPanel* UGP_ActionButtonArray;
	// Button Var
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<UEventActionButtonWidget> EventActionButtonClass;

	// Enemy Var
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UBorder* Brd_EnemyLevel;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* Txt_EnemyLevel;
};
