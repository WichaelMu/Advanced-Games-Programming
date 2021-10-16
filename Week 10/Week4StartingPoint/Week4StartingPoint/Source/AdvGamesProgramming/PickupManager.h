// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "PickupManager.generated.h"

class APickup;

UCLASS()
class ADVGAMESPROGRAMMING_API APickupManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Init(const TArray<FVector>& PossibleSpawnLocationsArg, TSubclassOf<APickup> WeaponPickupClassArg, float SpawnIntervalArg);


private:

	TArray<FVector> PossibleSpawnLocations;
	TSubclassOf<APickup> WeaponPickupClass;
	float SpawnInterval;
	const float PICKUP_LIFETIME = 20.f;
	FTimerHandle WeaponSpawnTimer;

	void SpawnWeaponPickup();

};
