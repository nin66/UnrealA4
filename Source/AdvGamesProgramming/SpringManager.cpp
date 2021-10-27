// Fill out your copyright notice in the Description page of Project Settings.


#include "SpringManager.h"
#include "SakuraTree.h"
#include "EngineUtils.h"
#include "House.h"

// Sets default values
ASpringManager::ASpringManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpringManager::BeginPlay()
{
	Super::BeginPlay();
	//Logs the number of trees and houses 
	UE_LOG(LogTemp, Warning, TEXT("Number of sakura trees: %i"), AllSTrees.Num());
	UE_LOG(LogTemp, Warning, TEXT("Number of houses: %i"), AllHouses.Num());
	
}

// Called every frame
void ASpringManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void ASpringManager::GenerateSakuraTrees(const TArray<FVector>& Vertices, int32 Width, int32 Height)
{
	//initialise 2 random floats to help the randomization of tree and house generation
	float RandomNumber1 = FMath::RandRange(1, Vertices.Num() - 1);
	float RandomNumber = FMath::RandRange(0, Vertices.Num() - Width);
	

	//further empties all the meshes in the world just before we regenerate them
	for (TActorIterator<ASakuraTree> It(GetWorld()); It; ++It)
	{
		(*It)->Destroy();
	}
AllSTrees.Empty();

   for (TActorIterator<AHouse> It(GetWorld()); It; ++It)
   {
	(*It)->Destroy();
	
   }
AllHouses.Empty();

//Generate the trees and houses for summer
	//NOTE: the logic is the same as the tree manager cpp file - check that file for more details 
	for (int i = Width, Edge=0; i < RandomNumber1; i += RandomNumber / 10, Edge+=Width)
	{
		if (i % Width != 0 || i != 1 + Edge) {
				ASakuraTree* NewSTree = GetWorld()->SpawnActor<ASakuraTree>(Vertices[i], FRotator::ZeroRotator, FActorSpawnParameters());
				AllSTrees.Add(NewSTree);
			
		}
	}
	for (int i = Width, Edge = 0; i < RandomNumber; i += RandomNumber1 / 10, Edge += Width)
	{
		if ((i % Width != 0 || i != 1 + Edge) && RandomNumber1 != RandomNumber) {
			AHouse* NewHouse = GetWorld()->SpawnActor<AHouse>(Vertices[i], FRotator::ZeroRotator, FActorSpawnParameters());
			AllHouses.Add(NewHouse);
		}
	}
}

