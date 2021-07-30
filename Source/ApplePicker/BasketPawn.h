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
	TArray<class UStaticMeshComponent*> Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* CollisionVolume;

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

	UFUNCTION()
	void OnBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
	
	void InitBaskets();
	void RemoveBasket();
	int BasketsLeft();
};
