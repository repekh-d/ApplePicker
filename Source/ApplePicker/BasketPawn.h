// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/TimelineComponent.h"
#include "BasketPawn.generated.h"


UCLASS()
class APPLEPICKER_API ABasketPawn : public APawn
{
	GENERATED_BODY()

	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> Mesh;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> Material;
		ConstructorHelpers::FObjectFinderOptional<UCurveFloat> BasketDestructionCurve;
		FConstructorStatics() :
			Mesh(TEXT("/Game/Models/Basket.Basket")),
			Material(TEXT("/Game/Materials/BasketWood.BasketWood")),
			BasketDestructionCurve(TEXT("/Game/Blueprints/BasketDestructionCurve.BasketDestructionCurve"))
		{
		}
		void Get()
		{
			Mesh.Get();
			Material.Get();
			BasketDestructionCurve.Get();
		}
	};
	static FConstructorStatics ConstructorStatics;

	UPROPERTY()
	class USceneComponent* DummyRoot;

	// Mesh
	UPROPERTY()
	TArray<class UStaticMeshComponent*> Mesh;

	// Collision bounding box
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* CollisionVolume;

	FOnTimelineFloat UpdateFunctionFloat;
	FOnTimelineEventStatic FinishFunction;

public:
	UPROPERTY()
	float MaxSpeed;

	UPROPERTY(EditAnywhere)
	class UCurveFloat* DestructionTimelineCurve;

	// Basket destruction animation
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UTimelineComponent* DestructionTimeline;

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

private:
	UFUNCTION()
	void UpdateTimeline(float Output);
};
