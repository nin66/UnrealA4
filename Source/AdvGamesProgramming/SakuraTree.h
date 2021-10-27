// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SakuraTree.generated.h"

UCLASS()
class ADVGAMESPROGRAMMING_API ASakuraTree : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASakuraTree();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Tree; //used to form the tree just like in winter but we will also attach the tree leaves to it 
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* TreeLeaves; //mesh for the sakura leaves 


	float RandomHeight; //randomize height just like tree.cpp

};
