// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MW.generated.h"

/**
 * 
 */
UCLASS()
class ADVGAMESPROGRAMMING_API UMW : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	

public:
	static void Log(FString);
};
