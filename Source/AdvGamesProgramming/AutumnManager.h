// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TreeManager.h"
#include "AutumnManager.generated.h"

/**
 * 
 */
UCLASS()
class ADVGAMESPROGRAMMING_API AAutumnManager : public ATreeManager
{
	GENERATED_BODY()
public:
	void GenerateTrees(const TArray<FVector>& Vertices, int32 Width, int32 Height) override;
	UPROPERTY(VisibleAnywhere, Category = "Autumn Trees")
		TArray<class AAutumnTree*> AllAutumnTrees; //array to store/delete the trees
};
