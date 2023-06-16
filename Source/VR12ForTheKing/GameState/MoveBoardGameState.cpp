// Fill out your copyright notice in the Description page of Project Settings.


#include "../GameState/MoveBoardGameState.h"

TArray<AMyCharacter*>& AMoveBoardGameState::GetPlayerCharacterArray()
{
	return PlayerCharacterArray;
}
