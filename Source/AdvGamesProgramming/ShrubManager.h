// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShrubManager.generated.h"

UCLASS()
class ADVGAMESPROGRAMMING_API AShrubManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShrubManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void GenerateShrubs(const TArray<FVector>& Vertices, int32 Width, int32 Height); //method to generate the shrubs and the houses

	UPROPERTY(VisibleAnywhere, Category = "Grass Shrubs")
		TArray<class AGrassShrub*> AllShrubs; //array to store/delete the shrubs
	UPROPERTY(VisibleAnywhere, Category = "Houses")
		TArray<class AHouse*> AllHouses; //array to store/delete the houses

};
