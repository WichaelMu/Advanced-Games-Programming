// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AIManager.generated.h"

class ANavigationNode;

UCLASS()
class ADVGAMESPROGRAMMING_API AAIManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAIManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	TArray<ANavigationNode*> GeneratePath(ANavigationNode*, ANavigationNode*);

	void PopulateNodes();
	void CreateAgents();

	void GenerateNodes(const TArray<FVector>&, int32, int32);
	void AddConnection(ANavigationNode*, ANavigationNode*);
	UPROPERTY(EditAnywhere)
		float AllowedAngle;

	UPROPERTY(EditAnywhere, Category = "AI Properties")
		int32 NumAI;
	
	UPROPERTY(VisibleAnywhere, Category = "Navigation Nodes")
		TArray<ANavigationNode* > AllNodes;

	UPROPERTY(VisibleAnywhere, Category = "Agents")
		TArray<class AEnemyCharacter*> AllAgents;

	UPROPERTY(EditAnywhere, Category = "Agents")
		TSubclassOf<class AEnemyCharacter> AgentToSpawn;

	ANavigationNode* RandomNode();

	ANavigationNode* FindFurthestNode(const FVector&);
	ANavigationNode* FindNearestNode(const FVector&);
};
