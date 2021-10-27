// Fill out your copyright notice in the Description page of Project Settings.


#include "TreeManager.h"
#include"Tree.h"
#include "House.h"
#include "EngineUtils.h"

// Sets default values
ATreeManager::ATreeManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	 
}

// Called when the game starts or when spawned
void ATreeManager::BeginPlay()
{
	Super::BeginPlay();

	//Logs the number of trees and houses 
	UE_LOG(LogTemp, Warning, TEXT("Number of trees: %i"), AllTrees.Num());
	UE_LOG(LogTemp, Warning, TEXT("Number of houses: %i"), AllHouses.Num());
	
}

// Called every frame
void ATreeManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void ATreeManager::GenerateTrees(const TArray<FVector>& Vertices, int32 Width, int32 Height)
{
	//initialise 2 random floats to help the randomization of tree and house generation
	float RandomNumber1 = FMath::RandRange(1, Vertices.Num() - 1); 
	float RandomNumber = FMath::RandRange(0, Vertices.Num() - Width);

	//further empties all the meshes in the world just before we regenerate them
	for (TActorIterator<ATree> It(GetWorld()); It; ++It)
	{
		(*It)->Destroy();
	}
	AllTrees.Empty(); 
	for (TActorIterator<AHouse> It(GetWorld()); It; ++It)
	{
		(*It)->Destroy();
	}
	AllHouses.Empty();

	
	//Generate the trees and houses for winter 
	for (int i = Width, Edge=0; i < RandomNumber1; i += RandomNumber / 10, Edge+=Width) //in the for loop, we declare int i and edge for looping. The edge is just to check for edges and i will increment at a random number between 0 and the total number of vertices - width so that it doesn't get to the back of the mesh component
	{
	
			if (i % Width != 0 || i!=1+Edge) //further check for edges 
			{
				ATree* NewTree = GetWorld()->SpawnActor<ATree>(Vertices[i], FRotator::ZeroRotator, FActorSpawnParameters()); //we add a tree randomly based on the coordinates of the mesh
				AllTrees.Add(NewTree); //add the new tree to the array 
			}
		
	}
	for (int i = Width, Edge=0; i < RandomNumber; i += RandomNumber1 / 10, Edge+=Width) //loops very similarly to the trees, but we are reversing the placements of the 2 randomized floats
	{
		
			if ((i % Width != 0 || i!=1+Edge)  && RandomNumber1 != RandomNumber)  //further checks for edges and checks if the random floats aren't the same 
			{
				RandomRotation = FMath::FRandRange(0, 360); //generate a random rotation between 0 and 360 degrees 
				AHouse* NewHouse = GetWorld()->SpawnActor<AHouse>(Vertices[i], FRotator(0, RandomRotation, 0), FActorSpawnParameters()); //Generates houses based on the for loop and if statement and a random rotation so that it doesn't look like it flipped
				AllHouses.Add(NewHouse); //add the new house to the array 
			}
		
	}

}




