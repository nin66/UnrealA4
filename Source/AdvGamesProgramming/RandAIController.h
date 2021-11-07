// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISenseConfig_Sight.h"
#include "AIController.h"
#include "RandAIController.generated.h"

/**
 * 
 */
UCLASS()
class ADVGAMESPROGRAMMING_API ARandAIController : public AAIController
{
	GENERATED_BODY()
	

public:
    void BeginPlay() override;

private:
    UPROPERTY()
        TArray<AActor*> Waypoints;

    UFUNCTION()
        ATargetPoint* GetRandomWaypoint();

    UFUNCTION()
        void GoToRandomWaypoint();

public:
    //"OnMoveCompleted" Called on completing current movement request, override with custom instructions
    void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;


private:
    FTimerHandle TimerHandle;

    //component variables for sightAI sense
    UAIPerceptionComponent* PerceptionComponent;
    UAISenseConfig_Sight* SightConfig;

    //constructor
    ARandAIController();

    //function to bind
    UFUNCTION()
        void onTargetPerceptionUpdate(AActor* Actor, FAIStimulus Stimulus);

};

