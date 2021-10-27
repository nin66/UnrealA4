// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpringManager.generated.h"

UCLASS()
class ADVGAMESPROGRAMMING_API ASpringManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpringManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void GenerateSakuraTrees(const TArray<FVector>& Vertices, int32 Width, int32 Height); //method to generate the trees and the houses

	UPROPERTY(VisibleAnywhere, Category = "Sakura Trees")
		TArray<class ASakuraTree*> AllSTrees; //array to store/delete the trees
	UPROPERTY(VisibleAnywhere, Category = "Houses")
		TArray<class AHouse*> AllHouses; //array to store/delete the houses

};
