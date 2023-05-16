// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

// Event Enum

UENUM(BlueprintType)
enum class EEventType : uint8
{
	NONE,
	ENEMY,
	STRUCTURE,
	TOWN,
	MERCHANT,
	DUNGEON,
};

// Event Action

UENUM(BlueprintType)
enum class ETileEventActionType : uint8
{
	Battle,
	Retreat,
};

// Action Enum

UENUM(BlueprintType)
enum class EFactionType : uint8
{
	Player,
	Enemy
};

UENUM(BlueprintType)
enum class EActionType : uint8
{
	Attack,
	Buff
};

UENUM(BlueprintType)
enum class EActionRange : uint8
{
	Single,
	All,
};

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