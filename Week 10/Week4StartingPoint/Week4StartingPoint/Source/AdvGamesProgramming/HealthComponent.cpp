// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Engine/GameEngine.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerHUD.h"
#include "PlayerCharacter.h"
#include "MW.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	MaxHealth = 100;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	CurrentHealth = MaxHealth;

	UpdateHealthBar();
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...


	/*if (GEngine && GetOwner()->GetLocalRole() == ROLE_AutonomousProxy)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("Current Health: %f"), CurrentHealth));
	}*/
}

void UHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// ...


	DOREPLIFETIME(UHealthComponent, CurrentHealth);
}

void UHealthComponent::OnTakeDamage(float Damage)
{
	CurrentHealth -= Damage;
	
	if (CurrentHealth <= 0)
	{
		OnDeath();
	}
}

void UHealthComponent::OnDeath()
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetOwner());

	if (PlayerCharacter)
	{
		PlayerCharacter->OnDeath();
	}
	else
	{
		UMW::Log("PlayerCharacter is nullptr!");
	}
}

float UHealthComponent::HealthPercentageRemaining() const
{
	return CurrentHealth / MaxHealth;
}

void UHealthComponent::UpdateHealthBar()
{
	if (GetOwner()->GetLocalRole() == ENetRole::ROLE_AutonomousProxy)
	{
		//UMW::Log("Update Health Bar GetLocalRole is AutonomousProxy!");
		AHUD* PlayerHUD = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD();

		if (PlayerHUD)
		{
			//UMW::Log("UpdateH Health Bar PlayerHUD is valid!");

			APlayerHUD* PlayerHealthBar = Cast<APlayerHUD>(PlayerHUD);

			if (PlayerHealthBar)
			{
				PlayerHealthBar->SetPlayerHealthBarPercent(HealthPercentageRemaining());
			}
			/*else
			{
				UMW::LogError("Update Health Bar PlayerHealthBar is nullptr!");
			}*/
		}
		/*else
		{
			UMW::LogError("Update Health Bar PlayerHUD is nullptr!");
		}*/
	}
	/*else
	{
		UMW::LogError("Update Health Bar GetLocalRole is not AutonomousProxy!");
	}*/
}

