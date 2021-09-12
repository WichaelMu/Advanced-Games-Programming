// Fill out your copyright notice in the Description page of Project Settings.


#include "KismetProceduralMeshLibrary.h"
#include "AIManager.h"
#include "ProcedurallyGeneratedMap.h"

// Sets default values
AProcedurallyGeneratedMap::AProcedurallyGeneratedMap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	MeshComponent = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Mesh Component"));

	bRegenerateMap = false;

	PerlinScale = 1000.f;
	PerlinRoughness = .1f;
}

// Called when the game starts or when spawned
void AProcedurallyGeneratedMap::BeginPlay()
{
	Super::BeginPlay();
	

	/*
	TArray<FVector> Vertices;
	Vertices.Add(FVector::ZeroVector);
	Vertices.Add(FVector(0, 100, 0));
	Vertices.Add(FVector(100, 100, 0));
	Vertices.Add(FVector(100, 0, 0));

	TArray<int32> Triangles;
	for (int32 i = 0; i < Vertices.Num(); i += 3)
	{
		if (i % 2 == 0)
		{
			Triangles.Add(i);
			Triangles.Add(i+1);
			Triangles.Add(i+3);
		}
		else
		{
			Triangles.Add(i);
			Triangles.Add(i-2);
			Triangles.Add(i-1);
		}
	}

	TArray<FVector2D> UVCoords;
	UVCoords.Add(FVector2D::ZeroVector);
	UVCoords.Add(FVector2D(0, 1));
	UVCoords.Add(FVector2D(1, 1));
	UVCoords.Add(FVector2D(1, 0));

	FOccluderVertexArray Normals;
	TArray<FColor> VertexColours;
	TArray<FProcMeshTangent> Tangent;
	MeshComponent->CreateMeshSection(0, Vertices, Triangles, Normals, UVCoords, VertexColours, Tangent, true); */
}

// Called every frame
void AProcedurallyGeneratedMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (bRegenerateMap)
	{
		ClearMap();
		GenerateMap();
		bRegenerateMap = !bRegenerateMap;
	}
}

bool AProcedurallyGeneratedMap::ShouldTickIfViewportsOnly() const
{
	return true;
}

void AProcedurallyGeneratedMap::GenerateMap()
{

	float PerlinOffset = FMath::RandRange(-10000.0f, 10000.0f);

	for (int32 y = 0; y < Height; ++y)
	{
		for (int32 x = 0; x < Width; ++x)
		{
			float Perlin = FMath::PerlinNoise2D(FVector2D(x + PerlinOffset, y + PerlinOffset) * PerlinRoughness) * PerlinScale;
			Vertices.Add(FVector(GridSize * x, GridSize * y, Perlin));
		}
	}

	for (int32 y = 0; y < Height - 1; ++y)
	{
		for (int32 x = 0; x < Width - 1; ++x)
		{
			Triangles.Add(y * Width + x);
			Triangles.Add((y + 1) * Width + x);
			Triangles.Add(y * Width + x + 1);
			Triangles.Add(y * Width + x + 1);
			Triangles.Add((y + 1) * Width + x);
			Triangles.Add((y + 1) * Width + x + 1);
		}
	}

	for (int32 y = 0; y < Height; ++y)
	{
		for (int32 x = 0; x < Width; ++x)
		{
			UVCoords.Add(FVector2D(x, y));
		}
	}

	UKismetProceduralMeshLibrary::CalculateTangentsForMesh(Vertices, Triangles, UVCoords, Normals, Tangents);
	TArray<FColor> VertexColours;
	MeshComponent->CreateMeshSection(0, Vertices, Triangles, Normals, UVCoords, VertexColours, Tangents, true);

	UE_LOG(LogTemp, Warning, TEXT("Vertices Count: %i | UVCoords Count: %i | Triangles Count: %i"), Vertices.Num(), UVCoords.Num(), Triangles.Num());

	if (AIManager)
	{
		AIManager->GenerateNodes(Vertices, Width, Height);
	}
}

void AProcedurallyGeneratedMap::ClearMap()
{
	Vertices.Empty();
	Triangles.Empty();
	UVCoords.Empty();

	MeshComponent->ClearAllMeshSections();
}

