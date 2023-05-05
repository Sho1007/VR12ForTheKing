// Fill out your copyright notice in the Description page of Project Settings.


#include "../Character/MyCharacter.h"

#include "Components/CapsuleComponent.h"
#include "../HexGrid/HexTile.h"
#include "../MyGameModeBase.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("CapsuleComponent");
	SetRootComponent(CapsuleComponent);

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComponent");
	SkeletalMeshComponent->SetupAttachment(RootComponent);
}

void AMyCharacter::Init(AMyGameModeBase* NewGameMode)
{
	GameMode = NewGameMode;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickEnabled(false);
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//GEngine->AddOnScreenDebugMessage(-1, 60, FColor::Cyan, FString::Printf(TEXT("Distance : %f"), FVector::Distance(Destination, GetActorLocation())));
	if (FVector::Distance(Destination, GetActorLocation()) <= ReachSuccessRadius)
	{
		ReachToDestination();
	}
	else
	{
		FVector Direction = Destination - GetActorLocation();
		Direction.Normalize();
		AddActorWorldOffset(Direction * MoveSpeed * DeltaTime);
	}
}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
}
void AMyCharacter::ReachToDestination_Implementation()
{
	SetActorTickEnabled(false);
	if (bIsMoveMode)
	{
		GameMode->ReachToTile();
		return;
	}
}

void AMyCharacter::SetCurrentTile(AHexTile* NewCurrentTile)
{
	CurrentTile = NewCurrentTile;
}

void AMyCharacter::SetDestination(FVector NewDestination, float NewSpeed, float NewRadius)
{
	if (NewSpeed)
	{
		MoveSpeed = NewSpeed;
	}
	if (NewRadius != ReachSuccessRadius)
	{
		ReachSuccessRadius = NewRadius;
	}
	Destination = FVector(NewDestination.X, NewDestination.Y, GetActorLocation().Z);
	//GEngine->AddOnScreenDebugMessage(-1, 60, FColor::Cyan, FString::Printf(TEXT("SetDestination Called : %s"), *Destination.ToString()));
	SetActorTickEnabled(true);
}

AHexTile* AMyCharacter::GetCurrentTile()
{
	return CurrentTile;
}

float AMyCharacter::GetTurnSpeed_Implementation(const int32 CurrentRoundCount)
{
	return 0.0f;
}