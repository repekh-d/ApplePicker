// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BattleLogEntryInfo.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class APPLEPICKER_API UBattleLogEntryInfo : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Missed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Action;
	
	UBattleLogEntryInfo();
};
