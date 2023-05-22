// Fill out your copyright notice in the Description page of Project Settings.


#include "../Component/MoveManagerComponent.h"

#include "../Widget/MoveWidget.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UMoveManagerComponent::UMoveManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...

	MoveJudgeArray.Init(true, 5);
}


// Called when the game starts
void UMoveManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	Init();
}

void UMoveManagerComponent::Init()
{
	// Todo : Load DataFile

	Day = 0;
	Turn = 0;

	CreateMoveWidget();
}

void UMoveManagerComponent::PrepareTurn()
{
	// Todo : Update Turn Widget;
	Turn++;
	if (Turn / 10 > Day)
	{
		Day++;
	}

	CheckMoveCount();
	MoveWidget->UpdateMoveJudge(MoveJudgeArray);
}

void UMoveManagerComponent::ExecuteTurn()
{
	
}

void UMoveManagerComponent::FinishTurn()
{
}

void UMoveManagerComponent::CheckMoveCount()
{
	MovableCount = 2;
	for (int i = 2; i < 5; ++i)
	{
		MoveJudgeArray[i] = UKismetMathLibrary::RandomBoolWithWeight(0.5f);
		if (MoveJudgeArray[i])
		{
			MovableCount++;
		}
	}
}

const UMoveWidget* UMoveManagerComponent::GetMoveWidget() const
{
	return MoveWidget;
}

void UMoveManagerComponent::CreateMoveWidget()
{
	check(MoveWidgetClass != nullptr && GEngine != nullptr);
	MoveWidget = CreateWidget<UMoveWidget>(GEngine->GetFirstLocalPlayerController(GetWorld()), MoveWidgetClass);
	check(MoveWidget != nullptr);
	MoveWidget->AddToPlayerScreen(0);
	MoveWidget->HideEventInfoWidget();
	MoveWidget->HideEventWidget();
}