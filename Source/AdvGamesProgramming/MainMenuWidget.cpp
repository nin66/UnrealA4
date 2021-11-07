// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "Components/Button.h"
#include "MainGameInstance.h"




void UMainMenuWidget::OnStartButtonPressed()
{
	UE_LOG(LogTemp, Warning, TEXT("Start Button Pressed"))

		//the commented lines are an attempt to make it work on c++
		if (UMainGameInstance* GameInstance = Cast<UMainGameInstance>(GetGameInstance()))
		{
			//GameInstance->CreateSession(TEXT("Test Session"));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Unable to find the GameInstance"))
		}
}

void UMainMenuWidget::OnJoinButtonPressed()
{
	UE_LOG(LogTemp, Warning, TEXT("Join Button Pressed"))
		if (UMainGameInstance* GameInstance = Cast<UMainGameInstance>(GetGameInstance()))
		{
			//GameInstance->FindSession(TEXT("Test Session"));

		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Unable to find GameInstance"))
		}
}

bool UMainMenuWidget::Initialize()
{
	Super::Initialize();
	if (ButtonStart && ButtonJoin)
	{
		//ButtonStart->OnClicked.AddDynamic(this, &UMainMenuWidget::OnStartButtonPressed);
		//ButtonJoin->OnClicked.AddDynamic(this, &UMainMenuWidget::OnJoinButtonPressed);
		return true;
	}
	return false;
}
