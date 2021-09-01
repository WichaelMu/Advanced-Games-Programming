// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "AIManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "HealthComponent.h"
#include "NavigationNode.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	GetCharacterMovement()->bOrientRotationToMovement = true;

	CurrentAgentState = EAgentState::PATROL;

	DetectedActor = nullptr;
	bCanSeeActor = false;
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	

	PerceptionComponent = FindComponentByClass<UAIPerceptionComponent>();

	if (PerceptionComponent)
	{
		PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyCharacter::SensePlayer);
	}

	UHealthComponent* Health = FindComponentByClass<UHealthComponent>();
	
	if (Health)
	{
		HealthComponent = Health;
	}
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);

	float HealthPercentage = HealthComponent->HealthPercentageRemaining();
	
	if (CurrentAgentState == EAgentState::PATROL)
	{
		AgentPatrol();

		if (bCanSeeActor)
		{
			if (HealthPercentage >= 40.f)
			{
				CurrentAgentState = EAgentState::ENGAGE;
				Path.Empty();
			}

			if (HealthPercentage < 40.f)
			{
				CurrentAgentState = EAgentState::EVADE;
				Path.Empty();
			}
		}
	}
	else if (CurrentAgentState == EAgentState::ENGAGE)
	{
		AgentEngage();

		if (!bCanSeeActor)
		{
			CurrentAgentState = EAgentState::PATROL;
		}
		else if (HealthPercentage < 40.f)
		{
			CurrentAgentState = EAgentState::EVADE;
			Path.Empty();
		}

	}
	else if (CurrentAgentState == EAgentState::EVADE)
	{
		AgentEvade();

		if (!bCanSeeActor)
		{
			CurrentAgentState = EAgentState::PATROL;
		}

		if (HealthPercentage >= 40.f)
		{
			CurrentAgentState = EAgentState::ENGAGE;
			Path.Empty();
		}
	}

	MoveAlongPath();
}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyCharacter::AgentPatrol()
{
	if (Path.Num() == 0)
	{
		Path = Manager->GeneratePath(CurrentNode, Manager->RandomNode());
	}
}

void AEnemyCharacter::AgentEngage()
{
	if (bCanSeeActor)
	{
		if (DetectedActor)
		{
			FVector DetectedActorLocation = DetectedActor->GetActorLocation();

			FVector DirectionToTarget = (DetectedActorLocation - GetActorLocation()).GetSafeNormal();
			Fire(DirectionToTarget);

			Path = Manager->GeneratePath(CurrentNode, Manager->FindNearestNode(DetectedActorLocation));
		}
	}
}

void AEnemyCharacter::AgentEvade()
{
	if (Path.Num() == 0)
	{
		Path = Manager->GeneratePath(CurrentNode, Manager->FindFurthestNode(DetectedActor->GetActorLocation()));
	}
	
	if (bCanSeeActor)
	{
		if (DetectedActor)
		{
			FVector DetectedActorLocation = DetectedActor->GetActorLocation();
			FVector DirectionToTarget = (DetectedActorLocation - GetActorLocation()).GetSafeNormal();

			Fire(DirectionToTarget);
		}
	}
}

void AEnemyCharacter::SensePlayer(AActor* ActorSensed, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed())
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Detected"));
		DetectedActor = ActorSensed;
		bCanSeeActor = true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Lost"));
		bCanSeeActor = false;
	}
}

void AEnemyCharacter::MoveAlongPath()
{
	// We're using this twice, don't bother recalculating the result!
	bool bIsNearCurrentNode = (GetActorLocation() - CurrentNode->GetActorLocation()).IsNearlyZero(100.f);

	if (bIsNearCurrentNode && Path.Num() > 0)
	{
		CurrentNode = Path.Pop();
	}
	else if (!bIsNearCurrentNode)
	{
		AddMovementInput((CurrentNode->GetActorLocation() - GetActorLocation()).GetSafeNormal());
	}
}

