// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TreeManager.generated.h"

UCLASS()
class ADVGAMESPROGRAMMING_API ATreeManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATreeManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere, Category = "Trees")
		TArray<class ATree*> AllTrees; //array to store/delete the trees

	void GenerateTrees(const TArray<FVector>& Vertices, int32 Width, int32 Height); //method to generate the trees and the houses

	UPROPERTY(VisibleAnywhere, Category = "Houses")
		TArray<class AHouse*> AllHouses; //array to store/delete the houses
	float RandomRotation; //used to randomize the rotation

	
};
