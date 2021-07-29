// Fill out your copyright notice in the Description page of Project Settings.


#include "BasketPawn.h"

// Sets default values
ABasketPawn::ABasketPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

// Called to bind functionality to input
void ABasketPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

