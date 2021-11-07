// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OnlineSubsystem.h"
#include "Engine.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "MainGameInstance.generated.h"

/**
 *
 */
//This file is basically similar to the week 11 solution, however, due to existing problems when loading level from the menu, we decided to leave it as it is to show our attempt in getting it to work on c++
UCLASS()
class ADVGAMESPROGRAMMING_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()

private:
	TSubclassOf<class UUserWidget> MainMenuWidgetClass;
	class UMainMenuWidget* Menu;

	IOnlineSubsystem* Subsystem;
	IOnlineSessionPtr SessionInterface;
	TSharedPtr<FOnlineSessionSearch> SessionSearch;

public:
	UMainGameInstance(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable)
		void LoadMenu();
	virtual void Init();
	void CreateSession(FName SessionName);
	void DestroySession(FName SessionName);
	void FindSession(FName SessionName);
	void JoinSession(FName SessionName);

private:

	void OnCreateSessionComplete(FName SessionName, bool bSuccess);
	void OnDestroySessionComplete(FName SessionName, bool bSuccess);
	void OnFindSessionComplete(bool bSuccess);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

};
