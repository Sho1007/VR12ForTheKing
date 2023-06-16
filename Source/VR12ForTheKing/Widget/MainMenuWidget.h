// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
class UButton;
UCLASS()
class VR12FORTHEKING_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
private:
	UFUNCTION()
	void NewGameButtonOnClicked();
	UFUNCTION()
	void JoinGameButtonOnClicked();
	UFUNCTION()
	void QuitButtonOnClicked();

private:
	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget))
	UButton* Btn_NewGame;
	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget))
	UButton* Btn_JoinGame;
	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget))
	UButton* Btn_Quit;
};