// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerGameMode.h"
#include "EngineUtils.h"
#include "Engine/World.h"
#include "PickupManager.h"
#include "ProcedurallyGeneratedMap.h"
#include "Engine/Engine.h"
#include "MW.h"
#include "PlayerCharacter.h"


void AMultiplayerGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessages)
{
	Super::InitGame(MapName, Options, ErrorMessages);

	// ...

	for (TActorIterator<AProcedurallyGeneratedMap> it(GetWorld()); it; ++it)
	{
		ProceduralMap = *it;
	}

	PickupManager = GetWorld()->SpawnActor<APickupManager>();
	PickupManager->Init(ProceduralMap->Vertices, WeaponPickupClass, SpawnFrequencyInSeconds);

}

void AMultiplayerGameMode::Respawn(AController* Controller)
{
	if (Controller)
	{
		GEngine->AddOnScreenDebugMessage(01, 2.5f, FColor::Blue, FString::Printf(TEXT("Respawning")));
		UMW::Log("Respawning");
		AActor* PlayerStart = ChoosePlayerStart(Controller);

		if (PlayerStart)
		{
			FTimerDelegate TimerDelegate;
			TimerDelegate.BindUFunction(this, FName("SpawnPlayer"), Controller, PlayerStart);

			GetWorldTimerManager().SetTimer(SpawnTimer, TimerDelegate, 5, false, 5);
		}
	}
	else
	{
		UMW::LogError("Controller is nullptr!");
	}
}

void AMultiplayerGameMode::SpawnPlayer(AController* Controller, AActor* PlayerStart)
{
	APawn* SpawnedPawn = GetWorld()->SpawnActor<APawn>(DefaultPawnClass, PlayerStart->GetActorLocation(), PlayerStart->GetActorRotation());
	if (SpawnedPawn)
	{
		UMW::Log("Should Possess");
		Controller->Possess(SpawnedPawn);
	}
	else
	{
		UMW::LogError("Spawned Pawn is nullptr!");
	}
}
