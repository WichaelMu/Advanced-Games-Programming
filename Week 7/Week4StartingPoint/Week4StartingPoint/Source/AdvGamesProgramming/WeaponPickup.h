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

	void OnGenerate() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float BulletDamage;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float MuzzleVelocity;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int32 MagazineSize;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float WeaponAccuracy;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		EWeaponPickupRarity Rarity;


private:

	void SetBulletDamage(const bool&);
	void SetMuzzleVelocity(const bool&);
	void SetMagazineSize(const bool&);
	void SetWeaponAccuracy(const bool&);
};
