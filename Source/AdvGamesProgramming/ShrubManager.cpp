// Fill out your copyright notice in the Description page of Project Settings.


#include "ShrubManager.h"
#include "GrassShrub.h"
#include "House.h"
#include "EngineUtils.h"


// Sets default values
AShrubManager::AShrubManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShrubManager::BeginPlay()
{
	Super::BeginPlay();
	//Logs the number of shrubs and houses 
	UE_LOG(LogTemp, Warning, TEXT("Number of shrubs: %i"), AllShrubs.Num());
	UE_LOG(LogTemp, Warning, TEXT("Number of houses: %i"), AllHouses.Num());
	
}

// Called every frame
void AShrubManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void AShrubManager::GenerateShrubs(const TArray<FVector>& Vertices, int32 Width, int32 Height)
{
	//initialise 2 random floats to help the randomization of tree and house generation
	float RandomNumber1 = FMath::RandRange(1, Vertices.Num() - 1);
	float RandomNumber = FMath::RandRange(0, Vertices.Num() - Width);
	
	//further empties all the meshes in the world just before we regenerate them
	for (TActorIterator<AGrassShrub> It(GetWorld()); It; ++It)
	{
		(*It)->Destroy();
	}
	AllShrubs.Empty();
	for (TActorIterator<AHouse> It(GetWorld()); It; ++It)
	{
		(*It)->Destroy();	
	}
	AllHouses.Empty();

	//Generate the shrubs and houses for summer
	//NOTE: the logic is the same as the tree manager cpp file - check that file for more details 
	for (int i = Width, Edge=0; i < RandomNumber1; i += RandomNumber / 10, Edge+=Width)
	{
		
		if (i % Width != 0 || i != 1 + Edge) {
				AGrassShrub* NewShrub = GetWorld()->SpawnActor<AGrassShrub>(Vertices[i], FRotator::ZeroRotator, FActorSpawnParameters());
				AllShrubs.Add(NewShrub);
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

