// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"
#include "UObject/ConstructorHelpers.h"
#include "MW.h"


APlayerHUD::APlayerHUD()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> PlayerHUDObject(TEXT("/Game/Widgets/PlayerHUDWidget"));

	if (PlayerHUDObject.Succeeded())
	{
		PlayerHUDClass = PlayerHUDObject.Class;

		if (PlayerHUDClass)
		{
			CurrentPlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDClass);
			if (CurrentPlayerHUDWidget)
			{
				CurrentPlayerHUDWidget->AddToViewport();

				HealthProgressBar = Cast<UProgressBar>(CurrentPlayerHUDWidget->GetWidgetFromName(TEXT("ProgHealthBar")));

				DeadScreen = Cast<UImage>(CurrentPlayerHUDWidget->GetWidgetFromName(TEXT("DEADSCREEN")));
				DeadMessage = Cast<UTextBlock>(CurrentPlayerHUDWidget->GetWidgetFromName(TEXT("DEADTEXT")));
			}
			else
			{
				UMW::Log("CurrentPlayerHUDWidget is nullptr!");
			}
		}
		else
		{
			UMW::Log("CurrentPlayerHUDWidget is nullptr!");
		}
	}
	else
	{
		UMW::Log("Couldn't find /Game/Widgets/PlayerHUDWidget!");
	}
}

void APlayerHUD::SetPlayerHealthBarPercent(const float& Percent)
{
	if (HealthProgressBar)
	{
		HealthProgressBar->SetPercent(Percent);

		if (Percent <= 0)
		{
			UMW::Log("In Des");
			DeadHUD();
		}
		else
		{
			UMW::Log("Show HUD");
			AliveHUD();
		}
	}
}

void APlayerHUD::DeadHUD()
{
	if (CurrentPlayerHUDWidget)
	{
		HealthProgressBar->SetVisibility(ESlateVisibility::Hidden);

		DeadScreen->SetVisibility(ESlateVisibility::Visible);
		DeadMessage->SetVisibility(ESlateVisibility::Visible);
	}
}

void APlayerHUD::AliveHUD()
{
	if (CurrentPlayerHUDWidget)
	{
		HealthProgressBar->SetVisibility(ESlateVisibility::Visible);

		DeadScreen->SetVisibility(ESlateVisibility::Hidden);
		DeadMessage->SetVisibility(ESlateVisibility::Hidden);
	}
}

