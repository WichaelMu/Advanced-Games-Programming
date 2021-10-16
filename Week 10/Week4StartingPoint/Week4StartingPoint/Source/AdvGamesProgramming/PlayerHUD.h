// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class ADVGAMESPROGRAMMING_API APlayerHUD : public AHUD
{
	GENERATED_BODY()
	

public:

	// Sets default values for this actor's properties
	APlayerHUD();


public:

	void SetPlayerHealthBarPercent(const float& Percent);

	void DeadHUD();
	void AliveHUD();

private:

	TSubclassOf<UUserWidget> PlayerHUDClass;
	UUserWidget* CurrentPlayerHUDWidget;

	UProgressBar* HealthProgressBar;
	UImage* DeadScreen;
	UTextBlock* DeadMessage;

};
