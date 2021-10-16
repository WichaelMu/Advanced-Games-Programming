// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "TimerManager.h"
#include "MultiplayerGameMode.generated.h"

class AProcedurallyGeneratedMap;
class APickupManager;
class APickup;
class AController;
class APawn;

/**
 * 
 */
UCLASS()
class ADVGAMESPROGRAMMING_API AMultiplayerGameMode : public AGameMode
{
	GENERATED_BODY()
	

public:

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<APickup> WeaponPickupClass;
	UPROPERTY(EditDefaultsOnly)
		float SpawnFrequencyInSeconds;

	void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessages) override;


	void Respawn(AController* Controller);


private:

	AProcedurallyGeneratedMap* ProceduralMap;
	APickupManager* PickupManager;

	UFUNCTION()
		void SpawnPlayer(AController* Controller, AActor* PlayerStart);
	FTimerHandle SpawnTimer;

};
