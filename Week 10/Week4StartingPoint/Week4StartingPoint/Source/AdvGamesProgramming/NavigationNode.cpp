// Fill out your copyright notice in the Description page of Project Settings.


#include "NavigationNode.h"
#include "DrawDebugHelpers.h"
#include "Components/SceneComponent.h"

// Sets default values
ANavigationNode::ANavigationNode()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LocationComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Location Component."));
	RootComponent = LocationComponent;

}

// Called when the game starts or when spawned
void ANavigationNode::BeginPlay()
{
	Super::BeginPlay();
	
	const FVector Origin = GetActorLocation();

	for (auto it = ConnectedNodes.CreateConstIterator(); it; ++it)
	{
		DrawDebugLine(GetWorld(), Origin, (*it)->GetActorLocation(), FColor::Blue, true);
	}
}

// Called every frame
void ANavigationNode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ANavigationNode::DirectionTo(ANavigationNode* Bearing)
{
	return (Bearing->GetActorLocation() - GetActorLocation()).GetSafeNormal();
}

float ANavigationNode::FScore()
{
	return GScore + HScore;
}

