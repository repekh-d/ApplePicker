// Fill out your copyright notice in the Description page of Project Settings.


#include "AppleTree.h"
#include "Apple.h"

// Sets default values
AAppleTree::AAppleTree() :
	MovementDirection(1.f),
	RemainsTillDrop(0.f),
	MovementSpeed(3000.f),
	DropInterval(1.f)
{
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> Mesh;
		FConstructorStatics() :
			Mesh(TEXT("/Game/Models/AppleTree.AppleTree"))
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
void AAppleTree::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAppleTree::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Move
	AddActorLocalOffset(GetActorRightVector() * MovementSpeed * MovementDirection * DeltaTime);

	FVector Location = GetActorLocation();
	// Change direction if hit side or with 2% possibility
	if (Location.Y > 3000.f)
	{
		MovementDirection = -1.f;
	}
	else if (Location.Y < -3000.f)
	{
		MovementDirection = 1.f;
	}
	else if (FMath::RandRange(0.f, 1.f) > 0.98f)
	{
		MovementDirection *= -1.f;
	}

	// Check whether it's time to drop apple
	RemainsTillDrop -= DeltaTime;
	if (RemainsTillDrop <= 0.f)
	{
		FBox TreeBBox = GetComponentsBoundingBox();
		FVector SpawnPoint = FVector(0.f, (TreeBBox.Min.Y + TreeBBox.Max.Y) / 2.f, TreeBBox.Min.Z);
		AApple* Apple = GetWorld()->SpawnActor<AApple>(SpawnPoint, FRotator(0.f, 0.f, 0.f));
		Apple->SetActorScale3D(FVector(0.3f, 0.3f, 0.3f));

		RemainsTillDrop = DropInterval;
	}
}

