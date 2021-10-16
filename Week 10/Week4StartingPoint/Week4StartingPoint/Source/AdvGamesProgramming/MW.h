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
	static void LogError(FString);

	template <typename T>
	static T* RandomTArray(const TArray<T*>& Array);

	template <typename T>
	static T RandomTArray(const TArray<T>& Array);

};

template <typename T>
inline T* UMW::RandomTArray(const TArray<T*>& Array)
{
	uint32 Random = FMath::RandRange(0, Array.Num() - 1);
	return Array[Random];
}

template <typename T>
inline T UMW::RandomTArray(const TArray<T>& Array)
{
	uint32 Random = FMath::RandRange(0, Array.Num() - 1);
	return Array[Random];
}
