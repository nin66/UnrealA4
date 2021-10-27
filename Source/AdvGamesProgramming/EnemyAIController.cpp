// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine.h"
#include "EnemyAI.h"
#include "EnemyAIController.h"

//"OnMoveCompleted" Called on completing current movement request
void AEnemyAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	//returns the enemy character pawn we defined
	AEnemyAI* EnemyAI = Cast<AEnemyAI>(GetPawn());
	//if not null, the enemy will move to the next waypoint in waypointOrder
	if (EnemyAI)
	{
		EnemyAI->MoveToWaypoints();
	}
}

AEnemyAIController::AEnemyAIController()
{

	//create AI perception component
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("SightPerceptionComponent"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(FName("Sight Config"));

	//sight sense configs
	SightConfig->SightRadius = 700;
	SightConfig->LoseSightRadius = 800;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	//assign sight to the ai perception component and bind ontarget function
	PerceptionComponent->ConfigureSense(*SightConfig);
	PerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());
	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController::onTargetPerceptionUpdate);
}

void AEnemyAIController::onTargetPerceptionUpdate(AActor* Actor, FAIStimulus Stimulus)
{
	//get the perceived actors and fill up array of actors seen by ue4 ai sight senses
	TArray<AActor*> PerceivedActors;
	PerceptionComponent->GetPerceivedActors(TSubclassOf<UAISense_Sight>(), PerceivedActors);

	//get the number of perceived actors (player and any other enemies that walk past) in the sight field
	bool isSeen = PerceivedActors.Contains(Actor);
	int NumberObjectSeen = PerceivedActors.Num();

	//print string message if actor is seen by ai sight
	FString text = FString(Actor->GetName() + " has just been " + (isSeen ? "spotted in" : "lost from") + " the enemies' view.");
	//print to debug log
	if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, text);
		}
	UE_LOG(LogTemp, Warning, TEXT("%s"), *text);
}