// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "Components/InputComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
	LookSensitivity = 1.f;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	bUseControllerRotationPitch = true;
}


// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Strafe", this, &APlayerCharacter::Strafe);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::Turn);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
}


void APlayerCharacter::MoveForward(float Throw)
{
	FRotator ForwardRotation = GetControlRotation();
	ForwardRotation.Pitch = 0;
	ForwardRotation.Roll = 0;

	AddMovementInput(ForwardRotation.Vector(), Throw);
}


void APlayerCharacter::Strafe(float Throw)
{
	AddMovementInput(GetActorRightVector(), Throw);
}


void APlayerCharacter::LookUp(float Throw)
{
	AddControllerPitchInput(Throw * LookSensitivity);
}


void APlayerCharacter::Turn(float Throw)
{
	AddControllerYawInput(Throw * LookSensitivity);
}

/*
	RESEARCH TASK:
		1) What is frame rate dependence/independence?
			-	Frame rate dependence is where a game relies on the speed of the computer, e.g., to move
				objects around the game. For example, if you compare the movement of an object on a computer
				running at 120 frames per second, as compared to a computer running at 30 frames per second,
				we can expect the computer running at 120 frames per second to move the object further than
				the computer running at 30 frames per second, even if both objects began at the same time.
					-	For example: Move an object intended for 1 unit per frame. A frame rate
						dependent game will have different results, depending on the processing power
						of each device.
						1 unit per frame means that the computer with more powerful hardware will move
						further than the computer with less powerful hardware.
			-	Frame rate independence is where a game does not rely on the speed of the computer. For example,
				if you want to move an object at 1 unit per frame, regardless of hardware. Unlike frame rate
				dependent games, where stronger computers can move the object further, frame rate independent
				games ensure a consistent speed of the object, irrespective of computer hardware. This is done
				by calculating the time between frames - the current frame and its preceding frame and multiply
				this value by the intended speed of the object, i.e., 1 unit per frame * DeltaTime.

		2) Why do we not need to deal with DeltaSeconds when using APawn::AddMovementInput in an ACharacter class derived actor?
			-	APawn::AddMovementInput already takes DeltaSeconds into account when using it.
				
				**STACKTRACE**

			-	APawn::AddMovementInput will call APawn::Internal_AddMovementInput which adds movement to an FVector ControlInputVector.
				ControlInputVector is only used in Internal_GetPendingMovementInputVector() in which it returns its value.
				Internal_GetPendingMovementInputVector()'s only call is in UPawnMovementComponent::GetPendingInputVector().
				UFloatingPawnMovement::ApplyControlInputToVelocity(float DeltaTime) calls UPawnMovementComponent::GetPendingInputVector().
				UFloatingPawnMovement::ApplyControlInputToVelocity(float DeltaTime) takes in delta time from UFloatingPawnMovement::TickComponent.

			-	It is therefore not necessary to deal with DeltaSeconds, as it is already taken into account.

		3) Why do we not need to deal with DeltaSeconds when using the APawn::AddControllerPitchInput and APawn::AddControllerYawInput functions?
			-	Unreal's mouse movement is already calculated with the difference in positions between the previous
				frame. Therefore, having mouse movement be multiplied by DeltaSeconds is not necessary and
				APawn::AddControllerPitchInput doesn't require a multiplication of DeltaSeconds.
			-	As for not needing to multiply by DeltaSeconds for the function itself, no clue. But I found that
				in this case, because we're using the mouse, it is not necessary.

			-	Could it be that, in the case of PitchInput, the inputs for the rotations are accumulated each tick, making it unecessary to consider
				DeltaSeconds. See APlayerController::RotationInput, its documented that way. This is sort of what I wrote above, but instead
				accumulates the axis every tick.
*/