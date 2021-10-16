// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupManager.h"
#include "MW.h"
#include "Engine/World.h"
#include "Pickup.h"
#include "Engine/Engine.h"

// Sets default values
APickupManager::APickupManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APickupManager::BeginPlay()
{
	Super::BeginPlay();
	
	// ...

	GetWorldTimerManager().SetTimer(WeaponSpawnTimer, this, &APickupManager::SpawnWeaponPickup, SpawnInterval, true, 0);
}

// Called every frame
void APickupManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickupManager::Init(const TArray<FVector>& PossibleSpawnLocationsArg, TSubclassOf<APickup> WeaponPickupClassArg, float SpawnIntervalArg)
{
	PossibleSpawnLocations = PossibleSpawnLocationsArg;
	WeaponPickupClass = WeaponPickupClassArg;
	SpawnInterval = SpawnIntervalArg;
}

void APickupManager::SpawnWeaponPickup()
{
	FVector RandomSpawnPoint = UMW::RandomTArray<FVector>(PossibleSpawnLocations);

	APickup* WeaponPickup = GetWorld()->SpawnActor<APickup>(WeaponPickupClass, RandomSpawnPoint + FVector(0, 0, 100), FRotator::ZeroRotator);
	WeaponPickup->SetLifeSpan(PICKUP_LIFETIME);

	GEngine->AddOnScreenDebugMessage(01, 1.f, FColor::Green, FString::Printf(TEXT("Pickup Spawned")));
}

