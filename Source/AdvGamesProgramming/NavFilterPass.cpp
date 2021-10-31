// Fill out your copyright notice in the Description page of Project Settings.

#include "NavAreaCostlyTerrain.h"
#include "NavFilterPass.h"

UNavFilterPass::UNavFilterPass()
{
	//create navigation filter area
	FNavigationFilterArea Desert = FNavigationFilterArea();

	//set parameters
	Desert.AreaClass = UNavAreaCostlyTerrain::StaticClass();
	Desert.bOverrideEnteringCost = true;
	Desert.EnteringCostOverride = 0.0f;
	Desert.bOverrideTravelCost = true;
	Desert.TravelCostOverride = 0.8f;

	//add to array of areas for the filter.
	Areas.Add(Desert);

}
