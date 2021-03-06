// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AppleTree.generated.h"

UCLASS()
class APPLEPICKER_API AAppleTree : public AActor
{
	GENERATED_BODY()

	UPROPERTY()
	class USceneComponent* DummyRoot;

	UPROPERTY()
	class UStaticMeshComponent* Mesh;

	float MovementDirection;
	float RemainsTillDrop;

public:
	UPROPERTY(EditAnywhere)
	float MovementSpeed;

	UPROPERTY(EditAnywhere)
	float DropInterval;
	
public:	
	// Sets default values for this actor's properties
	AAppleTree();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
