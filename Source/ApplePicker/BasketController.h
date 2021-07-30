// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasketController.generated.h"

/**
 * 
 */
UCLASS()
class APPLEPICKER_API ABasketController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY()
	class ABasketPawn* Basket;

	ABasketController();

	virtual void SetupInputComponent() override;
	void Move(float MoveIntensity);

protected:
	void virtual Tick(float DeltaTime) override;
	void virtual BeginPlay() override;
};
