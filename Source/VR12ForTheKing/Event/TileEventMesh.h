// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileEventMesh.generated.h"

class UArrowComponent;
UCLASS()
class VR12FORTHEKING_API ATileEventMesh : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATileEventMesh();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	const FTransform& GetCapturePosition() const;

protected:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	UArrowComponent* CapturePosition;
};
