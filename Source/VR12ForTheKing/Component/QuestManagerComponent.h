// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Engine/DataTable.h"

#include "QuestManagerComponent.generated.h"


class UQuestWidget;

UENUM(BlueprintType)
enum class EQuestType : uint8
{
	Location, KillMonster, Interact
};

USTRUCT(BlueprintType)
struct FStoryData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FText GameStory;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FVector StoryTargetLocation;
};

USTRUCT(BlueprintType)
struct FObjectiveData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FText ObjectName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString ObjectID;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 Quantiy;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool IsOptional;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		EQuestType QuestType;
};


USTRUCT(BlueprintType)
struct FQuestData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FText QuestName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FText QuestDescription;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<FObjectiveData> Ojective;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 XPReward;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TMap<FName, int32> ItemReward;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 GoldReward;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FText MainQuestName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FText SideQuestName;
};

USTRUCT(BlueprintType)
struct FQuestNPCData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FText NpcName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FText NpcNickName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UTexture2D* NpcImage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<FStoryData> StoryDataArray;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<FQuestData> Purpose;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bIsMain;
};

UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VR12FORTHEKING_API UQuestManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UQuestManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void DoNextQuest();
	FName GetCurrentMainQuest();

	UQuestWidget* GetQuestWidget() const;

	FQuestNPCData* FindQuestNPCData(FName TargetRow);

private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	UDataTable* QuestDataTable;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	TArray<FName> QuestArray;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	int32 CurrentQuestIndex;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	int32 CurrentStoryIndex;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	int32 CurrentDiscriptionIndex;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	TSubclassOf<UQuestWidget> QuestWidgetClass;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	UQuestWidget* QuestWidget;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	TArray<FVector> CurrentQuest;
};