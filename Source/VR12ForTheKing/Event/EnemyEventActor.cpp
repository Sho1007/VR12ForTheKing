// Fill out your copyright notice in the Description page of Project Settings.


#include "../Event/EnemyEventActor.h"

AEnemyEventActor::AEnemyEventActor()
{
    EventInfo.EventType = EEventType::ENEMY;
}

const int32 AEnemyEventActor::GetEnemyNum() const
{
    return EventInfo.EnemyClassArray.Num();
}

const TArray<TSubclassOf<AMyCharacter>>& AEnemyEventActor::GetEnemyArray() const
{
    return EventInfo.EnemyClassArray;
}

void AEnemyEventActor::StartBattle()
{
    UE_LOG(LogTemp, Warning, TEXT("AEnemyEventActor::StartBattle : Called"));
}