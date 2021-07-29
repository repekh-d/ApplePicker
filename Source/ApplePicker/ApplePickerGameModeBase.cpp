// Copyright Epic Games, Inc. All Rights Reserved.


#include "ApplePickerGameModeBase.h"
#include "BasketPawn.h"
#include "BasketController.h"

AApplePickerGameModeBase::AApplePickerGameModeBase()
{
	DefaultPawnClass = ABasketPawn::StaticClass();
	PlayerControllerClass = ABasketController::StaticClass();
}