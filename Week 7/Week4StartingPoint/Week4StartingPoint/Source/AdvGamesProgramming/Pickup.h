// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

class USceneComponent;
class UBoxComponent;

UCLASS()
class ADVGAMESPROGRAMMING_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	USceneComponent* PickupSceneComponent;
	UBoxComponent* PickupBoundingBox;

	UFUNCTION()
		virtual void OnEnterPickup(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	virtual void OnPickup(AActor*);

	UFUNCTION(BlueprintCallable)
		virtual void OnGenerate();

};
