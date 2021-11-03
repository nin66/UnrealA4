// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MultiplayerGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ADVGAMESPROGRAMMING_API AMultiplayerGameMode : public AGameMode
{
	GENERATED_BODY()
	
private:

	class AProcedurallyGeneratedMap* ProceduralMap;

public:

	void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessages) override;
	void Respawn(AController* Controller);
	UFUNCTION()
		void TriggerRespawn(AController* Controller);
};
