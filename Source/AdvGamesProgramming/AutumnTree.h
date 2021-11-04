// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tree.h"
#include "AutumnTree.generated.h"

/**
 * 
 */
UCLASS()
class ADVGAMESPROGRAMMING_API AAutumnTree : public ATree
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	AAutumnTree();
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* TreeLeaves; //mesh for the leaves 
};
