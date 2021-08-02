// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BattleLogEntryInfo.h"
#include "ApplePickerGameModeBase.generated.h"


UDELEGATE(BlueprintCallable)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCustomDelegate, UBattleLogEntryInfo*, Info);

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
	UPROPERTY(BlueprintAssignable, Category = "Game")
	FCustomDelegate OnNewAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite/*, meta = (MetaClass = "BattleLogEntryInfo")*/)
	TSubclassOf<UBattleLogEntryInfo> InfoClass;

	AApplePickerGameModeBase();

	void MissedApple();
	void CollectedApple();

	void RestartGame();

protected:
	virtual void BeginPlay() override;
};
