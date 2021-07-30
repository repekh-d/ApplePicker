// Fill out your copyright notice in the Description page of Project Settings.


#include "Apple.h"
#include "ApplePickerGameModeBase.h"
#include "Components/BoxComponent.h"

// Sets default values
AApple::AApple() :
	FallSpeed(5000.f)
{
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> Mesh;
		FConstructorStatics() :
			Mesh(TEXT("/Game/Models/Apple.Apple"))
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

	CollisionVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("Volume"));
	CollisionVolume->SetupAttachment(GetRootComponent());
	CollisionVolume->SetCollisionResponseToAllChannels(ECR_Overlap);
	
}

// Called when the game starts or when spawned
void AApple::BeginPlay()
{
	Super::BeginPlay();

	CollisionVolume->InitBoxExtent(GetComponentsBoundingBox().GetExtent());
}

// Called every frame
void AApple::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalOffset(GetActorUpVector() * (-FallSpeed) * DeltaTime);

	if (GetActorLocation().Z < -3000.f)
	{
		Destroy();
		AApplePickerGameModeBase* GameMode = Cast<AApplePickerGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->MissedApple();
		}
	}
}
