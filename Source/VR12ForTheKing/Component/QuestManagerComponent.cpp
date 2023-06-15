// Fill out your copyright notice in the Description page of Project Settings.


#include "../Component/QuestManagerComponent.h"

#include "../Widget/QuestWidget.h"


// Sets default values for this component's properties
UQuestManagerComponent::UQuestManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UQuestManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	
	QuestWidget = CreateWidget<UQuestWidget>(PC, QuestWidgetClass);
	checkf(QuestWidget != nullptr, TEXT("QuestWidget is not created"));

	QuestWidget->AddToViewport();

	FInputModeUIOnly InputMode;
	PC->SetInputMode(InputMode);
	PC->SetShowMouseCursor(true);
}


// Called every frame
void UQuestManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UQuestManagerComponent::DoNextQuest()
{
	FQuestNPCData* QuestNPCData = QuestDataTable->FindRow<FQuestNPCData>(GetCurrentMainQuest(), FString(""));
	
	if (QuestNPCData->StoryDataArray.Num() == CurrentStoryIndex)
	{
		CurrentStoryIndex = 0;
	}
	else
	{

	}
}

FName UQuestManagerComponent::GetCurrentMainQuest()
{
	return QuestArray[CurrentQuestIndex];
}

UQuestWidget* UQuestManagerComponent::GetQuestWidget() const
{
	return QuestWidget;
}

