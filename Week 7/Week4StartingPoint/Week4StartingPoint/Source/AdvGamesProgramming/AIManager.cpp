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


	AllowedAngle = .4f;
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
	for (auto& Node : AllNodes) { Node->GScore = INT_MAX; }

	TArray<ANavigationNode*> Open;
	Open.Add(Origin);
	Origin->GScore = 0;
	Origin->HScore = FVector::Dist(Origin->GetActorLocation(), Destination->GetActorLocation());

	while (Open.Num() > 0)
	{
		ANavigationNode* Current = Open[0];

		float LowestF = INT_MAX;
		for (int i = 1; i < Open.Num(); ++i)
		{
			if (Open[i]->FScore() < LowestF)
			{
				LowestF = Open[i]->FScore();
				Current = Open[i];
			}
		}

		Open.Remove(Current);

		if (Current == Destination)
		{
			TArray<ANavigationNode*> Path;

			ANavigationNode* Traverse = Destination;
			while (Traverse != Origin)
			{
				Path.Add(Traverse);
				Traverse = Traverse->CameFrom;
			}

			return Path;
		}

		for (auto it = Current->ConnectedNodes.CreateIterator(); it; ++it)
		{
			float FUpdatedCost = Current->GScore + FVector::DistSquared(Current->GetActorLocation(), (*it)->GetActorLocation());
			if (FUpdatedCost < (*it)->GScore)
			{
				(*it)->GScore = FUpdatedCost;
				(*it)->HScore = FVector::DistSquared((*it)->GetActorLocation(), Destination->GetActorLocation());
				(*it)->CameFrom = Current;

				if (!Open.Contains(*it))
				{
					Open.Add(*it);
				}
			}
		}
	}

	return TArray<ANavigationNode*>();

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

void AAIManager::GenerateNodes(const TArray<FVector>& Vertices, int32 Width, int32 Height)
{
	AllNodes.Empty();

	for (int32 y = 0; y < Height; ++y)
	{
		for (int32 x = 0; x < Width; ++x)
		{
			AllNodes.Add(GetWorld()->SpawnActor<ANavigationNode>(Vertices[y * Width + x], FRotator::ZeroRotator));
		}
	}

	for (int32 y = 0; y < Height - 1; ++y)
	{
		for (int32 x = 0; x < Width - 1; ++x)
		{
			ANavigationNode* C = AllNodes[y * Width + x];

			ANavigationNode* R = AllNodes[y * Width + x + 1];
			AddConnection(C, R);

			ANavigationNode* U = AllNodes[(y + 1) * Width + x];
			AddConnection(C, U);

			ANavigationNode* UR = AllNodes[(y + 1) * Width + x + 1];
			AddConnection(C, UR);
		}
	}
}

void AAIManager::AddConnection(ANavigationNode* FromNode, ANavigationNode* ToNode)
{
	FVector Direction = (ToNode->GetActorLocation() - FromNode->GetActorLocation()).GetSafeNormal();
	if (Direction.Z < AllowedAngle && Direction.Z > -AllowedAngle)
	{
		FromNode->ConnectedNodes.Add(ToNode);
		ToNode->ConnectedNodes.Add(FromNode);
	}
}

ANavigationNode* AAIManager::RandomNode()
{
	int SpawnNodeIndex = FMath::RandRange(0, AllNodes.Num() - 1);
	
	return AllNodes[SpawnNodeIndex];
}

ANavigationNode* AAIManager::FindFurthestNode(const FVector& Location)
{
	float Min = MIN_flt;
	ANavigationNode* Furthest = nullptr;

	for (ANavigationNode* Node : AllNodes)
	{
		// The square distance can be used as distance as we don't need the accurate result.
		float SqrDistance = FVector::DistSquared(Location, Node->GetActorLocation());
		if (SqrDistance > Min)
		{
			Min = SqrDistance;
			Furthest = Node;
		}
	}

	return Furthest;
}

ANavigationNode* AAIManager::FindNearestNode(const FVector& Location)
{
	float Max = MAX_FLT;
	ANavigationNode* Nearest = nullptr;

	for (ANavigationNode* Node : AllNodes)
	{
		// The square distance can be used as distance as we don't need the accurate result.
		float SqrDistance = FVector::DistSquared(Location, Node->GetActorLocation());
		if (SqrDistance < Max)
		{
			Max = SqrDistance;
			Nearest = Node;
		}
	}

	if (!Nearest)
	{
		UE_LOG(LogTemp, Warning, TEXT("NO NEAREST NODE!"));
	}

	return Nearest;
}

