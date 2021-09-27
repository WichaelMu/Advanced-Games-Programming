// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "PlayerCharacter.generated.h"

class UHealthComponent;

UCLASS()
class ADVGAMESPROGRAMMING_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UPROPERTY(EditAnywhere)
	float LookSensitivity;
	UPROPERTY(EditInstanceOnly)
	float SprintMultiplier;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Value);
	void Strafe(float Value);
	void LookUp(float Value);
	void Turn(float Value);
	void SprintStart();
	void SprintEnd();

	UFUNCTION(Server, Reliable)
		void ServerSprintStart();
	UFUNCTION(Server, Reliable)
		void ServerSprintEnd();


	UHealthComponent* HealthComponent;


	UFUNCTION(BlueprintImplementableEvent)
		void BlueprintReload();

	void Reload();


protected:

	float SprintMovementSpeed;
	float NormalMovementSpeed;


private:

	UCameraComponent* Camera;
	class UFirstPersonAnimInstance* AnimInstance;
};
