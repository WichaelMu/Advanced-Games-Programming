// Fill out your copyright notice in the Description page of Project Settings.


#include "AIManager.h"
#include "NavigationNode.h"
#include "Engine/World.h"
#include "NavigationNode.h"
#include "EnemyCharacter.h"
#include "EngineUtils.h"

// Sets default values
AAIManager::AAIManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAIManager::BeginPlay()
{
	Super::BeginPlay();
	
	PopulateNodes();
	CreateAgents();
}

// Called every frame
void AAIManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TArray<ANavigationNode*> AAIManager::GeneratePath(ANavigationNode* Origin, ANavigationNode* Destination)
{
	TArray<ANavigationNode*> empty;
	return empty;
}

void AAIManager::PopulateNodes()
{
	for (TActorIterator<ANavigationNode> it(GetWorld()); it; ++it)
	{
		AllNodes.Add(*it);
	}
}

void AAIManager::CreateAgents()
{
	for (uint8 i = 0; i < NumAI; ++i)
	{
		ANavigationNode* SpawnNode = RandomNode();

		AEnemyCharacter* SpawnedCharacter = GetWorld()->SpawnActor<AEnemyCharacter>(AgentToSpawn, SpawnNode->GetActorLocation(), FRotator(0, 0, 0));

		SpawnedCharacter->Manager = this;
		SpawnedCharacter->CurrentNode = SpawnNode;
	}
}

ANavigationNode* AAIManager::RandomNode()
{
	int SpawnNodeIndex = FMath::RandRange(0, AllNodes.Num() - 1);
	
	return AllNodes[SpawnNodeIndex];
}

