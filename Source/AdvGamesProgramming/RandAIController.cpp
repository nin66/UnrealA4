// Fill out your copyright notice in the Description page of Project Settings.

#include "RandAIController.h"
#include "Engine.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"


void ARandAIController::BeginPlay()
{
	Super::BeginPlay();
	//store all of the target waypoints in the game (get all actors of class equivilent)
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), Waypoints);

	GoToRandomWaypoint();
}


ARandAIController::ARandAIController()
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
	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ARandAIController::onTargetPerceptionUpdate);
}

//get a random target waypoint from the array with fmath random and cast the return value to correct type
ATargetPoint* ARandAIController::GetRandomWaypoint()
{
	float index = FMath::RandRange(0, Waypoints.Num() - 1);
	return Cast<ATargetPoint>(Waypoints[index]);
}

//moveTo makes AI go toward specified target goal actor and destination is constantly updated. no active path following
void ARandAIController::GoToRandomWaypoint()
{
	MoveToActor(GetRandomWaypoint());
}

//"OnMoveCompleted" Called on completing current movement request
void ARandAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);

	//using SetTimer to make the AI wait for 3 seconds (imitates 'looking around') before moving onto their next destination (being called in the function)
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ARandAIController::GoToRandomWaypoint, 3.0f, false);
}


void ARandAIController::onTargetPerceptionUpdate(AActor* Actor, FAIStimulus Stimulus)
{
	//get the perceived actors
	TArray<AActor*> PerceivedActors;
	PerceptionComponent->GetPerceivedActors(TSubclassOf<UAISense_Sight>(), PerceivedActors);

	//get the number of perceived actors (player and any other enemies that walk past) in the sight field
	bool bIsSeen = PerceivedActors.Contains(Actor);
	int NumberObjectSeen = PerceivedActors.Num();

	//print string message if actor is seen by ai sight
	FString text = FString(Actor->GetName() + " has just been " + (bIsSeen ? "spotted in" : "lost from") + " the enemies' view.");
	//print to debug log
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, text);
	}
	UE_LOG(LogTemp, Warning, TEXT("%s"), *text);
}