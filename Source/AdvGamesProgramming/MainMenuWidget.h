// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class ADVGAMESPROGRAMMING_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
private:
		UPROPERTY(meta = (BindWidget))
		class UButton* ButtonStart;
		UPROPERTY(meta = (BindWidget))
		UButton* ButtonJoin;
		virtual bool Initialize() override;
		UFUNCTION()
		void OnStartButtonPressed();
		UFUNCTION()
		void OnJoinButtonPressed();
	
};
