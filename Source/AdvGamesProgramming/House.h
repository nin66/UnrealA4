// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "House.generated.h"

UCLASS()
class ADVGAMESPROGRAMMING_API AHouse : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHouse();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, Replicated)
		UStaticMeshComponent* House; //house mesh 
	UPROPERTY(EditAnywhere, Replicated)
		UStaticMeshComponent* HouseRoof; //roof mesh 
	UPROPERTY(Replicated)
	float RandomScale; //used to randomise scale of the house

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
