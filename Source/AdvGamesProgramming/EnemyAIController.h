// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISenseConfig_Sight.h"
#include "EnemyAIController.generated.h"

/**
 *
 */
UCLASS()
class ADVGAMESPROGRAMMING_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
		//"OnMoveCompleted" Called on completing current movement request, override with custom instructions
		virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

	//component variables for sightAI sense
	UAIPerceptionComponent* PerceptionComponent;
	UAISenseConfig_Sight* SightConfig;


	//constructor
	AEnemyAIController();

	//function to bind
	UFUNCTION()
		void onTargetPerceptionUpdate(AActor* Actor, FAIStimulus Stimulus);

};
