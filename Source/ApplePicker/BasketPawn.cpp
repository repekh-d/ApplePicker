// Fill out your copyright notice in the Description page of Project Settings.


#include "BasketPawn.h"
#include "Components/BoxComponent.h"
#include "Apple.h"
#include "ApplePickerGameModeBase.h"


ABasketPawn::FConstructorStatics ABasketPawn::ConstructorStatics;

// Sets default values
ABasketPawn::ABasketPawn() :
	MaxSpeed(3000.f)
{
	ConstructorStatics.Init();
	PrimaryActorTick.bCanEverTick = true;

	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy"));
	RootComponent = DummyRoot;

	CollisionVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("Volume"));
	CollisionVolume->SetupAttachment(RootComponent);
	CollisionVolume->SetCollisionResponseToAllChannels(ECR_Overlap);

	for (size_t i = Mesh.Num(); i < 3; ++i)
	{
		static int count = 0;
		FString MeshName = TEXT("Mesh") + FString::FromInt(count++);
		Mesh.Add(CreateDefaultSubobject<UStaticMeshComponent>(FName(MeshName)));
		Mesh.Top()->SetStaticMesh(ConstructorStatics.Mesh.Get());
		Mesh.Top()->SetupAttachment(CollisionVolume);
		Mesh.Top()->AddLocalOffset(FVector(0.f, 0.f, i * 100.f));
	}

	DestructionTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("DestructionTimeline"));
}

// Called when the game starts or when spawned
void ABasketPawn::BeginPlay()
{
	Super::BeginPlay();

	CollisionVolume->SetBoxExtent(GetComponentsBoundingBox().GetExtent());
	//CollisionVolume->UpdateBounds();
	CollisionVolume->OnComponentBeginOverlap.AddDynamic(this, &ABasketPawn::OnBeginOverlap);

	// Init dynamic materials
	for (UStaticMeshComponent* Comp : Mesh)
	{
		UMaterialInstanceDynamic* DynMaterial = UMaterialInstanceDynamic::Create(ConstructorStatics.Material.Get(), this);
		Comp->SetMaterial(0, DynMaterial);
	}

	DestructionTimeline->SetLooping(false);
	// Bind timeline update function
	UpdateFunctionFloat.BindDynamic(this, &ABasketPawn::UpdateTimeline);
	DestructionTimelineCurve = ConstructorStatics.BasketDestructionCurve.Get();
	if (DestructionTimelineCurve)
	{
		DestructionTimeline->AddInterpFloat(DestructionTimelineCurve, UpdateFunctionFloat);
	}
	// Bind timeline finish function
	FinishFunction.BindLambda([this]()
	{
		if (Mesh.Num() > 0)
		{
			Mesh.Pop()->DestroyComponent();
		}
		if (Mesh.Num() == 0)
		{
			AApplePickerGameModeBase* GameMode = Cast<AApplePickerGameModeBase>(GetWorld()->GetAuthGameMode());
			if (GameMode)
			{
				GameMode->RestartGame();
			}
		}
	});
	DestructionTimeline->SetTimelineFinishedFunc(FinishFunction);
	
}

// Called every frame
void ABasketPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasketPawn::OnBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (Cast<AApple>(OtherActor))
	{
		OtherActor->Destroy();
		AApplePickerGameModeBase* GameMode = Cast<AApplePickerGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->CollectedApple();
		}
	}
}

void ABasketPawn::InitBaskets()
{
	// Create static mesh component
	for (size_t i = Mesh.Num(); i < 3; ++i)
	{
		static int count = 0;
		FString MeshName = TEXT("Mesh") + FString::FromInt(count++);
		Mesh.Add(NewObject<UStaticMeshComponent>(this, UStaticMeshComponent::StaticClass(), FName(MeshName)));
		Mesh.Top()->RegisterComponent();
		Mesh.Top()->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		Mesh.Top()->SetStaticMesh(ConstructorStatics.Mesh.Get());
		Mesh.Top()->AddLocalOffset(FVector(0.f, 0.f, i * 100.f));

		UMaterialInstanceDynamic* DynMaterial = UMaterialInstanceDynamic::Create(ConstructorStatics.Material.Get(), this);
		Mesh.Top()->SetMaterial(0, DynMaterial);
	}
}

void ABasketPawn::RemoveBasket()
{
	if (Mesh.Num() > 0)
	{
		DestructionTimeline->PlayFromStart();
	}
}

int ABasketPawn::BasketsLeft()
{
	return Mesh.Num();
}

void ABasketPawn::UpdateTimeline(float Output)
{
	auto Material = Cast<UMaterialInstanceDynamic>(Mesh.Top()->GetMaterial(0));
	if (Material)
	{
		Material->SetScalarParameterValue(TEXT("Intensity"), Output);
	}
}
