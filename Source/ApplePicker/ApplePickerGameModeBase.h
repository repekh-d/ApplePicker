// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ApplePickerGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class APPLEPICKER_API AApplePickerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	UPROPERTY()
	class AAppleTree* AppleTree;

	UPROPERTY()
	class ABasketPawn* BasketPawn;
	
public:
	AApplePickerGameModeBase();

protected:
	virtual void BeginPlay() override;
};
