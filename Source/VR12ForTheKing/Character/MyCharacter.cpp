// Fill out your copyright notice in the Description page of Project Settings.


#include "../Character/MyCharacter.h"

#include "Components/CapsuleComponent.h"
#include "../Component/BattleComponent.h"
#include "../Component/StatusComponent.h"
#include "../Component/InventoryComponent.h"
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

	BattleComponent = CreateDefaultSubobject<UBattleComponent>(TEXT("NewBattleComponent"));
	StatusComponent = CreateDefaultSubobject<UStatusComponent>(TEXT("StatusComponent"));
	// Todo : It will have To Seperate to Player and Enemy
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
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

	TestRandomizeStatus();
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
	else
	{
		BattleComponent->ReachToDestination();
	}
}

void AMyCharacter::SetMoveMode(bool NewMoveMode)
{
	bIsMoveMode = NewMoveMode;
}

void AMyCharacter::SetCurrentTile(AHexTile* NewCurrentTile)
{
	// Todo : Ÿ���� ���� �� (Collision �ְ�, EndOverlap) Leave
	// Ÿ�Ͽ� �� ����� �� (BeginOverlap) Arrive �����ϵ��� ����
	if (CurrentTile != nullptr)
	{
		CurrentTile->LeaveFromTile(this);
	}
	CurrentTile = NewCurrentTile;
	CurrentTile->ArriveToTile(this);
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

UTexture2D* AMyCharacter::GetCharacterImage()
{
	return CharacterImage;
}

void AMyCharacter::SetCharacterImage(UTexture2D* NewCharacterImage)
{
	CharacterImage = NewCharacterImage;
}

FText AMyCharacter::GetCharacterName() const
{
	return CharacterName;
}

void AMyCharacter::TestRandomizeStatus()
{
	StatusComponent->SetArmor(FMath::RandRange(0, 10));
	StatusComponent->SetCognition(FMath::RandRange(0, 10));
	StatusComponent->SetEvasion(FMath::RandRange(0, 10));
	StatusComponent->SetMaxFocus(FMath::RandRange(0, 10));
	StatusComponent->SetCurrentFocus(FMath::RandRange(0, StatusComponent->GetMaxFocus()));
	StatusComponent->SetIntelligence(FMath::RandRange(0, 10));
	StatusComponent->SetLuck(FMath::RandRange(0, 10));
	StatusComponent->SetResistance(FMath::RandRange(0, 10));
	StatusComponent->SetSpeed(FMath::RandRange(0, 10));
	StatusComponent->SetStrength(FMath::RandRange(0, 10));
	StatusComponent->SetTalent(FMath::RandRange(0, 10));
	StatusComponent->SetVitality(FMath::RandRange(0, 10));

	StatusComponent->SetMaxHP(FMath::RandRange(0, 10));
	StatusComponent->SetCurrentHP(FMath::RandRange(1, StatusComponent->GetMaxHP()));
	StatusComponent->SetAttackPower(FMath::RandRange(1, 10));
}

int32 AMyCharacter::GetTurnSpeed_Implementation(const int32 CurrentRoundCount)
{
	return 0.0f;
}	