// Fill out your copyright notice in the Description page of Project Settings.


#include "AutumnManager.h"
#include "AutumnTree.h"
#include "House.h"
#include "EngineUtils.h"
#include "Net/UnrealNetwork.h"

void AAutumnManager::GenerateTrees(const TArray<FVector>& Vertices, int32 Width, int32 Height)
{
	//ATreeManager::GenerateTrees(const TArray<FVector>& Vertices, int32 Width, int Height);
	//initialise 2 random floats to help the randomization of tree and house generation
	RandomNumber1 = FMath::RandRange(1, Vertices.Num() - 1);
	RandomNumber = FMath::RandRange(0, Vertices.Num() - Width);

	//further empties all the meshes in the world just before we regenerate them
	for (TActorIterator<AAutumnTree> It(GetWorld()); It; ++It)
	{
		(*It)->Destroy();
	}
	AllAutumnTrees.Empty();
	for (TActorIterator<AHouse> It(GetWorld()); It; ++It)
	{
		(*It)->Destroy();
	}
	AllHouses.Empty();


	//Generate the trees and houses for winter 
	for (int i = Width, Edge = 0; i < RandomNumber1; i += RandomNumber / 10, Edge += Width) //in the for loop, we declare int i and edge for looping. The edge is just to check for edges and i will increment at a random number between 0 and the total number of vertices - width so that it doesn't get to the back of the mesh component
	{

		if (i % Width != 0 || i != 1 + Edge) //further check for edges 
		{
			AAutumnTree* NewTree = GetWorld()->SpawnActor<AAutumnTree>(Vertices[i], FRotator::ZeroRotator, FActorSpawnParameters()); //we add a tree randomly based on the coordinates of the mesh
			AllAutumnTrees.Add(NewTree); //add the new tree to the array 
		}

	}
	for (int i = Width, Edge = 0; i < RandomNumber; i += RandomNumber1 / 10, Edge += Width) //loops very similarly to the trees, but we are reversing the placements of the 2 randomized floats
	{

		if ((i % Width != 0 || i != 1 + Edge) && RandomNumber1 != RandomNumber)  //further checks for edges and checks if the random floats aren't the same 
		{
			RandomRotation = FMath::FRandRange(0, 360); //generate a random rotation between 0 and 360 degrees 
			AHouse* NewHouse = GetWorld()->SpawnActor<AHouse>(Vertices[i], FRotator(0, RandomRotation, 0), FActorSpawnParameters()); //Generates houses based on the for loop and if statement and a random rotation so that it doesn't look like it flipped
			AllHouses.Add(NewHouse); //add the new house to the array 
		}

	}
}