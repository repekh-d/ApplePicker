// Fill out your copyright notice in the Description page of Project Settings.


#include "BasketPawn.h"

// Sets default values
ABasketPawn::ABasketPawn() :
	MaxSpeed(3000.f)
{
	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> Mesh;
		FConstructorStatics() :
			Mesh(TEXT("/Game/Models/Basket.Basket"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	PrimaryActorTick.bCanEverTick = true;

	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy"));
	RootComponent = DummyRoot;

	// Create static mesh component
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetStaticMesh(ConstructorStatics.Mesh.Get());
	Mesh->SetupAttachment(DummyRoot);
}

// Called when the game starts or when spawned
void ABasketPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasketPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

