// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

UCLASS()
class ADVGAMESPROGRAMMING_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
	public:
		/*Sets default values for this actor's properties*/
		ASpawnVolume();

	protected:
		//Called when the game starts or when spawned
		virtual void BeginPlay() override;

	public:
		//Called every frame
		virtual void Tick(float DeltaTime) override;

		/* Returns the WhereToSpawn subobject */
		FORCEINLINE class UBoxComponent* GetWhereToSpawn() const { return WhereToSpawn; }

		/* Find a random point within the BoxComponent */
		UFUNCTION(BlueprintPure, Category = "Spawning")
			FVector GetRandomPointInVolume();

		/* This function toggles whether or not the spawn volume spawns AI */
		UFUNCTION(BlueprintCallable, Category = "Spawning")
			void SetSpawningActive(bool bShouldSpawn);

	protected:
		/*the AI to spawn*/
		UPROPERTY(EditAnywhere, Category = "Spawning")
			TSubclassOf<class ACharacter> WhatToSpawn;

		FTimerHandle SpawnTimer;

		/*Minimum spawn delay*/
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
			float SpawnDelayRangeLow;

		/*Maxium spawn delay*/
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
			float SpawnDelayRangeHigh;


	private:
		UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
			class UBoxComponent* WhereToSpawn;

		/*Handle spawning a new AI*/
		void SpawnAI();

		/*the current spawn delay*/
		float SpawnDelay;
	};
