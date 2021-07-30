// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Apple.generated.h"

UCLASS()
class APPLEPICKER_API AApple : public AActor
{
	GENERATED_BODY()

	UPROPERTY()
	class USceneComponent* DummyRoot;

	UPROPERTY()
	class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* CollisionVolume;
	
public:
	UPROPERTY(EditAnywhere)
	float FallSpeed;

	// Sets default values for this actor's properties
	AApple();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
