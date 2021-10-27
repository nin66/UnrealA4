// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/World.h"
#include "Waypoint.h"
#include "EnemyAIController.h"
#include "EnemyAI.h"

// Sets default values
AEnemyAI::AEnemyAI()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyAI::BeginPlay()
{
	Super::BeginPlay();
	Cast<UCharacterMovementComponent>(GetMovementComponent())->bOrientRotationToMovement = true;

	//get all actors (array will fill up with all waypoints found in the level)
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWaypoint::StaticClass(), Waypoints);
	MoveToWaypoints();
	
}

// Called every frame
void AEnemyAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyAI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyAI::MoveToWaypoints()
{
	//return the controller that is possessing the pawn
	AEnemyAIController* EnemyAIController = Cast<AEnemyAIController>(GetController());

	//if the controller class used is the EnemyAIController (successfully cast in enemyAI blueprint details)
	//then in numerical order, if the current waypoint the enemy is moving to is less than the max waypoint number created,
	//iterate through the actors of type waypoints. If the waypoint is valid and equal to the "current" waypoint the enemy
	//is currently moving to, then the movement has completed and the current waypoint number increments. (reached 1, now new
	//target waypoint is 2.)



	if (EnemyAIController)
	{
		if (CurrentWaypoint <= Waypoints.Num())
		{
			for (AActor* Waypoint : Waypoints)
			{
				AWaypoint* WaypointItr = Cast<AWaypoint>(Waypoint);
				if (WaypointItr)
				{
					if (WaypointItr->GetWaypointOrder() == CurrentWaypoint)
					{
						EnemyAIController->MoveToActor(WaypointItr, 10.0f, false);
						CurrentWaypoint++;
						break;

					}

				}

			}
		}
	}
}

//for (same conditions as if statement above, except instead of being less than the current move-towards waypoint,
//executes if the current waypoint is equal to the max waypoint number created/generated in the level.)

// because we want to start the loop over completely, set the current waypoint to 0 before using 'continue' so the next increment
// allows the enemyAI to move back to the first waypoint in the order to repeat the loop after pushing it to 1.

	//for (int i = 0; i < Waypoints.Num(); ++i) {
	//	firstPartofLoop;
	//	if (CurrentWaypoint == Waypoints.Num()) {
	// CurrentWaypoint = 0;
	//		continue; //start over completely, set i to 0 before continue (the increment will be done afterwards pushing it to 1)
	//	}
	//	restofLoop;
	//}




