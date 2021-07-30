// Copyright Epic Games, Inc. All Rights Reserved.


#include "ApplePickerGameModeBase.h"
#include "BasketPawn.h"
#include "BasketController.h"
#include "AppleTree.h"


AApplePickerGameModeBase::AApplePickerGameModeBase()
{
	DefaultPawnClass = ABasketPawn::StaticClass();
	PlayerControllerClass = ABasketController::StaticClass();
}

void AApplePickerGameModeBase::BeginPlay()
{
	AppleTree = GetWorld()->SpawnActor<AAppleTree>(FVector(0.f, 0.f, 2000.f), FRotator(0.f, 0.f, 0.f));

	BasketPawn = Cast<ABasketPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (!BasketPawn)
		return;
	BasketPawn->SetActorLocation(FVector(0.f, 0.f, -2700.f));
	BasketPawn->SetActorScale3D(FVector(3.f, 3.f, 3.f));
}