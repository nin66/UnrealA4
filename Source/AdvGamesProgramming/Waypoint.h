// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Waypoint.generated.h"

/**
 *
 */
UCLASS()
class ADVGAMESPROGRAMMING_API AWaypoint : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	//get waypoint order
	int GetWaypointOrder();


private:
	//travel order of waypoints by assigned int number
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		int WaypointOrder;

};