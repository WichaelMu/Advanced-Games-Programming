// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponPickup.h"
#include "MW.h"

void AWeaponPickup::OnGenerate()
{
	APickup::OnGenerate();

	float Random = FMath::RandRange(0.f, 1.f);

	if (Random < .05f)
	{
		Rarity = EWeaponPickupRarity::LEGENDARY;

		SetBulletDamage(true);
		SetMuzzleVelocity(true);
		SetMagazineSize(true);
		SetWeaponAccuracy(true);
	}
	else if (Random < .15f)
	{
		Rarity = EWeaponPickupRarity::MASTER;

		SetBulletDamage(true);
		SetMuzzleVelocity(true);
		SetMagazineSize(true);
		SetWeaponAccuracy(true);

		int32 RandomBad = FMath::RandRange(0, 3);

		switch (RandomBad)
		{
		case 0:
			SetBulletDamage(false);
			break;
		case 1:
			SetMuzzleVelocity(false);
			break;
		case 2:
			SetMagazineSize(false);
			break;
		case 3:
			SetWeaponAccuracy(false);
			break;
		default:
			UMW::Log("ERROR IN SETTING MASTER");
			SetBulletDamage(false);
		}

	}
	else if (Random < .3f)
	{
		Rarity = EWeaponPickupRarity::RARE;

		SetBulletDamage(false);
		SetMuzzleVelocity(false);
		SetMagazineSize(false);
		SetWeaponAccuracy(false);

		int32 RandomGood = FMath::RandRange(0, 3);

		switch (RandomGood)
		{
		case 0:
			SetBulletDamage(true);
			break;
		case 1:
			SetMuzzleVelocity(true);
			break;
		case 2:
			SetMagazineSize(true);
			break;
		case 3:
			SetWeaponAccuracy(true);
			break;
		default:
			UMW::Log("ERROR IN SETTING RARE");
			SetBulletDamage(true);
		}
	}
	else
	{
		Rarity = EWeaponPickupRarity::COMMON;

		SetBulletDamage(false);
		SetMuzzleVelocity(false);
		SetMagazineSize(false);
		SetWeaponAccuracy(false);
	}
}

void AWeaponPickup::SetBulletDamage(const bool& SetGoodStat)
{
	BulletDamage = SetGoodStat ? FMath::RandRange(15.f, 30.f) : FMath::RandRange(2.f, 15.f);
}

void AWeaponPickup::SetMuzzleVelocity(const bool& SetGoodStat)
{
	MuzzleVelocity = SetGoodStat ? FMath::RandRange(10000.f, 20000.f) : FMath::RandRange(5000.f, 10000.f);
}

void AWeaponPickup::SetMagazineSize(const bool& SetGoodStat)
{
	MagazineSize = SetGoodStat ? FMath::RandRange(20, 100) : FMath::RandRange(1, 20);
}

void AWeaponPickup::SetWeaponAccuracy(const bool& SetGoodStat)
{
	WeaponAccuracy = SetGoodStat ? FMath::RandRange(0.95f, 1.0f) : FMath::RandRange(.8f, .95f);
}
