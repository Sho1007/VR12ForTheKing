// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSequenceTest.h"
#include "Kismet/GameplayStatics.h"

#include "LevelSequence.h"
#include "LevelSequencePlayer.h"
#include "LevelSequenceActor.h"

// Sets default values
ALevelSequenceTest::ALevelSequenceTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


// Called when the game starts or when spawned
void ALevelSequenceTest::BeginPlay()
{
	Super::BeginPlay();
	//PlayLevelSequence();
	
	
}
void ALevelSequenceTest::PlayLevelSequence()
{
	
	TArray<AActor*> LevelSequenceArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALevelSequenceActor::StaticClass(), LevelSequenceArray);
	Cast<ALevelSequenceActor>(LevelSequenceArray[0])->SequencePlayer->Play();
}
// Called every frame
void ALevelSequenceTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

