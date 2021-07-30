// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasketPawn.generated.h"

UCLASS()
class APPLEPICKER_API ABasketPawn : public APawn
{
	GENERATED_BODY()

	UPROPERTY()
	class USceneComponent* DummyRoot;

	UPROPERTY()
	class UStaticMeshComponent* Mesh;

public:
	UPROPERTY()
	float MaxSpeed;

	// Sets default values for this pawn's properties
	ABasketPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
