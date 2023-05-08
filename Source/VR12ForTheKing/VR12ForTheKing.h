// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

// Check Chance

UENUM(BlueprintType)
enum class EStatusType : uint8
{
	Armor,
	Awareness,
	Evasion,
	Focus,
	Intelligence,
	Luck,
	Resistance,
	Speed,
	Strength,
	Talent,
	Vitality,
};

USTRUCT(BlueprintType)
struct FAction
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture2D* Image;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText Discription;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Power;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 CheckCount;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 CheckPercent;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EStatusType StatType;
};