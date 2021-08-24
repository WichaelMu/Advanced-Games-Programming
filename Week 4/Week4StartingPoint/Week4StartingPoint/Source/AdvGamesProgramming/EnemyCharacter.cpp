// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "AIManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NavigationNode.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	GetCharacterMovement()->bOrientRotationToMovement = true;
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);

	if (Path.Num() == 0)
	{
		Path.Empty();
		Path = Manager->GeneratePath(CurrentNode, Manager->RandomNode());
	}
	else
	{
		if ((GetActorLocation() - CurrentNode->GetActorLocation()).IsNearlyZero(100.f))
		{
			CurrentNode = Path.Pop();
		}
		else
		{
			AddMovementInput((CurrentNode->GetActorLocation() - GetActorLocation()).GetSafeNormal());
		}
	}
}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

