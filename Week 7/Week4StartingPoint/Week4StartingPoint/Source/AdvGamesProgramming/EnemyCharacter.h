// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Perception/AIPerceptionTypes.h"
#include "EnemyCharacter.generated.h"

UENUM()
enum class EAgentState : uint8
{
	PATROL, ENGAGE, EVADE
};

class ANavigationNode;
class AAIManager;
class UAIPerceptionComponent;
class UHealthComponent;

UCLASS()
class ADVGAMESPROGRAMMING_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	void AgentPatrol();
	void AgentEngage();
	void AgentEvade();

	UFUNCTION()
		void SensePlayer(AActor* ActorSensed, FAIStimulus Stimulus);
	UAIPerceptionComponent* PerceptionComponent;

	UPROPERTY(EditAnywhere, meta = (UIMin="10.0", UIMax="1000.0", ClampMin="10.0", ClampMax="1000.0"))
		float PathfindingNodeAccuracy;

	UPROPERTY(EditAnywhere)
		EAgentState CurrentAgentState;


	UPROPERTY(VisibleAnywhere)
		AActor* DetectedActor;
	UPROPERTY(VisibleAnywhere)
		bool bCanSeeActor;


	UFUNCTION(BlueprintImplementableEvent)
		void Fire(FVector FireDirection);


	TArray<ANavigationNode*> Path;
	ANavigationNode* CurrentNode;
	AAIManager* Manager;


	UHealthComponent* HealthComponent;


private:


	void MoveAlongPath();


};
