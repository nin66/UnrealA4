// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GrassShrub.generated.h"

UCLASS()
class ADVGAMESPROGRAMMING_API AGrassShrub : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrassShrub();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Replicated)
		UStaticMeshComponent* GrassShrub; //used to initialise the shrubs
	UPROPERTY(Replicated)
	float RandomScale; //used to randomise scale

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
