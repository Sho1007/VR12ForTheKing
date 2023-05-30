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
	Cognition,
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

UENUM(BlueprintType)
enum class EItemRarity : uint8
{
	NONE,
	COMMON,
	UNCOMMON,
	RARE,
	ARTIFACT,
	SIZE,
};

UENUM(BlueprintType)
enum class EItemType : uint8
{
	NONE,
	CONSUMABLE,
	EQUIPMENT,
	SIZE,
};

UENUM(BlueprintType)
enum class EEquipmentType : uint8
{
	NONE,
	WEAPON,
	SHIELD,
	HEADGEAR,
	ARMOR,
	FOOTWEAR,
	NECKLACE,
	TRINKET,
	PIPE,
	SIZE,
};