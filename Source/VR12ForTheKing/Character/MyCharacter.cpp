// Fill out your copyright notice in the Description page of Project Settings.


#include "../Character/MyCharacter.h"

#include "Net/UnrealNetwork.h"
#include "Components/CapsuleComponent.h"

#include "../Component/BattleComponent.h"
#include "../Component/StatusComponent.h"
#include "../Component/InventoryComponent.h"
#include "../HexGrid/HexTile.h"
//#include "../MyGameModeBase.h"
#include "../GameState/MoveBoardGameState.h"
#include "../PlayerController/MoveBoardPlayerController.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("CapsuleComponent");
	SetRootComponent(CapsuleComponent);

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComponent");
	SkeletalMeshComponent->SetupAttachment(RootComponent);

	BattleComponent = CreateDefaultSubobject<UBattleComponent>(TEXT("NewBattleComponent"));
	StatusComponent = CreateDefaultSubobject<UStatusComponent>(TEXT("StatusComponent"));
	// Todo : It will have To Seperate to Player and Enemy
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Magenta, FString::Printf(TEXT("AMyCharacter::BeginPlay")));
	Super::BeginPlay();
	SetActorTickEnabled(false);
	
	TestRandomizeStatus();
}

void AMyCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyCharacter, CharacterData);
	DOREPLIFETIME(AMyCharacter, bIsMoveMode);
}

void AMyCharacter::NotifyActorBeginCursorOver()
{
	Super::NotifyActorBeginCursorOver();

	if (bIsMoveMode) return;

	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("AMyCharacter::NotifyActorBeginCursorOver")));
	AMoveBoardPlayerController* PC = GetWorld()->GetFirstPlayerController<AMoveBoardPlayerController>();
	check(PC);
	PC->SetFocusActor(this);
}

void AMyCharacter::NotifyActorEndCursorOver()
{
	Super::NotifyActorEndCursorOver();

	if (bIsMoveMode) return;

	AMoveBoardPlayerController* PC = GetWorld()->GetFirstPlayerController<AMoveBoardPlayerController>();
	check(PC);
	PC->ResetFocusActor(this);
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
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, FString::Printf(TEXT("ReachToDestination_Implementation")));

	SetActorTickEnabled(false);
	if (bIsMoveMode)
	{
		//GameMode->ReachToTile();
		AMoveBoardGameState* GameState = GetWorld()->GetGameState<AMoveBoardGameState>();
		check(GameState != nullptr);
		GameState->ReachToTile();
		return;
	}
	else
	{
		BattleComponent->ReachToDestination();
	}
}

void AMyCharacter::InitPlayerCharacter(FCharacterData* NewCharacterData)
{
	CharacterData = *NewCharacterData;

	// Update CharacterData to Component
}

AMyCharacter* AMyCharacter::GetActionTarget() const
{
	return BattleComponent->GetActionTarget();
}

void AMyCharacter::SetMoveMode(bool NewMoveMode)
{
	bIsMoveMode = NewMoveMode;
}

void AMyCharacter::SetCurrentTile(AHexTile* NewCurrentTile)
{
	if (CurrentTile != nullptr)
	{
		CurrentTile->LeaveFromTile(this);
	}
	CurrentTile = NewCurrentTile;
	CurrentTile->ArriveToTile(this);

	FVector NewLocation = NewCurrentTile->GetActorLocation();
	NewLocation.Z = this->GetActorLocation().Z;
	SetActorLocation(NewLocation);
}

void AMyCharacter::SetDestination(FVector NewDestination, float NewSpeed, float NewRadius)
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, FString::Printf(TEXT("New Destination : %s"), *NewDestination.ToString()));
	if (NewSpeed)
	{
		MoveSpeed = NewSpeed;
	}
	if (NewRadius != ReachSuccessRadius)
	{
		ReachSuccessRadius = NewRadius;
	}
	Destination = FVector(NewDestination.X, NewDestination.Y, GetActorLocation().Z);
	FVector Direction = Destination - this->GetActorLocation();
	this->SetActorRotation(Direction.Rotation());

	//this->SkeletalMeshComponent->PlayAnimation();

	//GEngine->AddOnScreenDebugMessage(-1, 60, FColor::Cyan, FString::Printf(TEXT("SetDestination Called : %s"), *Destination.ToString()));
	SetActorTickEnabled(true);
}

AHexTile* AMyCharacter::GetCurrentTile()
{
	return CurrentTile;
}

UTexture2D* AMyCharacter::GetCharacterImage()
{
	return CharacterData.CharacterImage;
}

void AMyCharacter::SetCharacterImage(UTexture2D* NewCharacterImage)
{
	CharacterData.CharacterImage = NewCharacterImage;
}

FText AMyCharacter::GetCharacterName() const
{
	return CharacterData.CharacterName;
}

int32 AMyCharacter::GetControllerIndex() const
{
	return CharacterData.ControllerIndex;
}

void AMyCharacter::SetControllerIndex(int32 NewControllerIndex)
{
	CharacterData.ControllerIndex = NewControllerIndex;
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

	StatusComponent->SetMaxHP(FMath::RandRange(1, 10));
	StatusComponent->SetCurrentHP(FMath::RandRange(1, StatusComponent->GetMaxHP()));
	StatusComponent->SetAttackPower(FMath::RandRange(1, 10));

	if (BattleComponent->GetFactionType() == EFactionType::Player)
	{
		StatusComponent->SetMaxHP(300);
		StatusComponent->SetCurrentHP(300);
		StatusComponent->SetAttackPower(300);
		StatusComponent->SetSpeed(300);
	}
}

int32 AMyCharacter::GetTurnSpeed_Implementation(const int32 CurrentRoundCount)
{
	return 0.0f;
}