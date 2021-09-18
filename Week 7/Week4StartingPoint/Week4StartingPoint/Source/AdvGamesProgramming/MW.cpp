// Fill out your copyright notice in the Description page of Project Settings.


#include "MW.h"


void UMW::Log(FString Message)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Message);
}
