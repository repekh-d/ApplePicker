// Fill out your copyright notice in the Description page of Project Settings.


#include "BasketController.h"
#include "BasketPawn.h"

#define PRINT(...) GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, FString::Printf(__VA_ARGS__));

ABasketController::ABasketController()
{

}

void ABasketController::SetupInputComponent()
{
    Super::SetupInputComponent();
    
    // Bind input
    InputComponent->BindAxis("MoveSideways", this, &ABasketController::Move);
}

void ABasketController::Move(float MoveIntensity)
{
    if (!Basket)
        return;
    Basket->AddMovementInput(Basket->GetActorRightVector(), Basket->MaxSpeed * MoveIntensity);
}

void ABasketController::Tick(float DeltaTime)
{
    if (!Basket)
        return;
    Basket->AddActorLocalOffset(Basket->ConsumeMovementInputVector() * DeltaTime);
}

void ABasketController::BeginPlay()
{
    Basket = Cast<ABasketPawn>(GetPawn());
}