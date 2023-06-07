// Fill out your copyright notice in the Description page of Project Settings.


#include "../Item/ItemBase.h"

#include "../Character/MyCharacter.h"

// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemBase::Use(AMyCharacter* OwnerCharacter)
{
	UE_LOG(LogTemp, Warning, TEXT("%s Use Item"), *OwnerCharacter->GetName());
}