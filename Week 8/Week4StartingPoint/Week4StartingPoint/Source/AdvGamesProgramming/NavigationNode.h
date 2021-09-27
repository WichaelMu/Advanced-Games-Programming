// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NavigationNode.generated.h"

class USceneComponent;

UCLASS()
class ADVGAMESPROGRAMMING_API ANavigationNode : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANavigationNode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere, Category = "Connected Nodes")
		TArray<ANavigationNode*> ConnectedNodes;

	FVector DirectionTo(ANavigationNode*);

	USceneComponent* LocationComponent;

	float FScore();
	float GScore, HScore;
	ANavigationNode* CameFrom;

	bool operator== (const ANavigationNode& ANN) { return this->GScore == ANN.GScore && this->HScore == ANN.HScore && this->CameFrom == ANN.CameFrom; }
	bool operator!= (const ANavigationNode& ANN) { return !(*this == ANN); }
};
