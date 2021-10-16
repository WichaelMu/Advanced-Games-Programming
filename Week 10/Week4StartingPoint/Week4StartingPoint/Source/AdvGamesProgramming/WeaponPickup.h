// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "WeaponPickup.generated.h"


UENUM(BlueprintType)
enum class EWeaponPickupRarity : uint8
{
	LEGENDARY, MASTER, RARE, COMMON
};


/**
 * 
 */
UCLASS()
class ADVGAMESPROGRAMMING_API AWeaponPickup : public APickup
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent)
		void OnPickup(AActor* ActorThatPickedUp) override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


	void OnGenerate() override;

	UFUNCTION(Server, Reliable)
		void ServerGenerate();

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly)
		float BulletDamage;
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly)
		float MuzzleVelocity;
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly)
		int32 MagazineSize;
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly)
		float WeaponAccuracy;
	
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly)
		EWeaponPickupRarity Rarity;


private:

	void SetBulletDamage(const bool&);
	void SetMuzzleVelocity(const bool&);
	void SetMagazineSize(const bool&);
	void SetWeaponAccuracy(const bool&);
};
