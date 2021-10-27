// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyAI.generated.h"

UCLASS()
class SEEK_API AEnemyAI : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyAI();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveToWaypoints();

private:
	//represents the waypoint that the enemyAI is currently running towards
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int CurrentWaypoint;

	//list of existing waypoints in the level
	TArray<AActor*> Waypoints;
};
