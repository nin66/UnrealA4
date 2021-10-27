// Fill out your copyright notice in the Description page of Project Settings.


#include "ProcedurallyGeneratedMap.h"
#include "KismetProceduralMeshLibrary.h"
#include "ShrubManager.h"
#include "UObject/ConstructorHelpers.h"
#include "AIManager.h"
#include "TreeManager.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "HealthComponent.h"
#include "Components/InputComponent.h"
#include "GrassShrub.h"
#include "Tree.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "EngineUtils.h"
#include "SpringManager.h"
#include "SakuraTree.h"
#include "House.h"


// Sets default values
AProcedurallyGeneratedMap::AProcedurallyGeneratedMap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Mesh Component"));

	PerlinScale = 1000.0f;
	PerlinRoughness = 0.1f;
	bRegenerateMap = false;
	
	//Using constructor helpers to find the object needed and to be able to access it from C++ instead of manunally adding it on the details panel
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> SnowMat(TEXT("MaterialInstanceConstant'/Game/Materials/PCGMaterials/Winter/SnowMaterialInstance.SnowMaterialInstance'"));
	SnowMaterial = SnowMat.Object; //Assign the snowmat.object to snow material for other methods 
	
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> SandMat(TEXT("MaterialInstanceConstant'/Game/Materials/PCGMaterials/Summer/SandMaterial_Inst.SandMaterial_Inst'"));
	SandMaterial = SandMat.Object; //Same as before to be able to access it for other methods in this cpp file. This is because i can only use constructor helpers in the constructor. 
	
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> SakuraMat(TEXT("MaterialInstanceConstant'/Game/Materials/PCGMaterials/Spring/SakuraLandScapeMaterial_Inst.SakuraLandScapeMaterial_Inst'"));
	SakuraMaterial = SakuraMat.Object; //Same as before to be able to access it for other methods in this cpp file. This is because i can only use constructor helpers in the constructor. 
	
	//Using constructor helpers to access the niagara systems from content browser
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> Snow(TEXT("NiagaraSystem'/Game/Assets/Niagara/SnowNiagaraEmitter_System.SnowNiagaraEmitter_System'"));
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> Rain(TEXT("NiagaraSystem'/Game/Assets/Niagara/RainNiagaraEmitter_System.RainNiagaraEmitter_System'"));
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> Sakura(TEXT("NiagaraSystem'/Game/Assets/Niagara/SakuraNiagaraEmitter_System.SakuraNiagaraEmitter_System'"));
	
	//Assigning the objects to the <UNiagaraSystem*> variables to be able to access it for other methods in this cpp file 
	RainEffect = Rain.Object;
	SnowEffect = Snow.Object;
	SakuraEffect = Sakura.Object; 
	
	

}

// Called when the game starts or when spawned
void AProcedurallyGeneratedMap::BeginPlay()
{
	Super::BeginPlay();
	
	/*
	TArray<FVector> Vertices;
	Vertices.Add(FVector(0.0f, 0.0f, 0.0f));
	Vertices.Add(FVector(0.0f, 100.0f, 0.0f));
	Vertices.Add(FVector(100.0f, 100.0f, 0.0f));
	Vertices.Add(FVector(100.0f, 0.0f, 0.0f));

	TArray<int32> Triangles;
	Triangles.Add(0);
	Triangles.Add(1);
	Triangles.Add(3);
	Triangles.Add(3);
	Triangles.Add(1);
	Triangles.Add(2);

	TArray<FVector2D> UVCoords;
	UVCoords.Add(FVector2D(0.0f, 0.0f));
	UVCoords.Add(FVector2D(0.0f, 1.0f));
	UVCoords.Add(FVector2D(1.0f, 1.0f));
	UVCoords.Add(FVector2D(1.0f, 0.0f));

	MeshComponent->CreateMeshSection(0, Vertices, Triangles, TArray<FVector>(), 
		UVCoords, TArray<FColor>(), TArray<FProcMeshTangent>(), true);
	*/

	//GenerateMap();

	//The particles will fall as soon as I play the project in the specific seasons provided. 
	//If it is in the winter season - only activating Winter manager
	if (WinterManager && !SummerManager && !SpringManager) {
		NewEffect = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			this,
			SnowEffect,                                           //The niagara system of snow fall will be activated via the SpawnSystemAtLocation function from the UNiagaraFunctionLibrary
			FVector(2850, 3430, 4890),
			FRotator::ZeroRotator,
			FVector::OneVector);
	}
	//If it is in the summer season - only activating Summer manager
	else if (SummerManager && !WinterManager && !SpringManager)
	{
		NewEffect = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			this,
			RainEffect,
			FVector(2850, 3430, 4890),                           //The niagara system of rain fall will be activated via the SpawnSystemAtLocation function from the UNiagaraFunctionLibrary
			FRotator::ZeroRotator,
			FVector::OneVector);
	}
	//If it is in the spring season - only activating Spring manager
	else if (SpringManager && !WinterManager && !SummerManager)
	{
		NewEffect = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			this,
			SakuraEffect,
			FVector(2850, 3430, 4890),                           //The niagara system of sakura flower fall will be activated via the SpawnSystemAtLocation function from the UNiagaraFunctionLibrary
			FRotator::ZeroRotator,
			FVector::OneVector);
	}

}

// Called every frame
void AProcedurallyGeneratedMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bRegenerateMap)
	{
		ClearMap();
		GenerateMap();
		bRegenerateMap = false;
	}
}

bool AProcedurallyGeneratedMap::ShouldTickIfViewportsOnly() const
{
	return true;
}

void AProcedurallyGeneratedMap::GenerateMap()
{
	float PerlinOffset = FMath::RandRange(-10000.0f, 10000.0f);
	for (int32 Y = 0; Y < Height; Y++)
	{
		for (int32 X = 0; X < Width; X++)
		{
			float Z = FMath::PerlinNoise2D(FVector2D(X * PerlinRoughness + PerlinOffset, Y * PerlinRoughness + PerlinOffset)) * PerlinScale;
			Vertices.Add(FVector(X * GridSize, Y * GridSize, Z));
			UVCoords.Add(FVector2D(X, Y));

			if (X != Width - 1 && Y != Height - 1)
			{
				Triangles.Add(Y * Width + X);
				Triangles.Add((Y + 1) * Width + X);
				Triangles.Add(Y * Width + X + 1);
				Triangles.Add(Y * Width + X + 1);
				Triangles.Add((Y + 1) * Width + X);
				Triangles.Add((Y + 1) * Width + X + 1);
			}
		}
	}

	UKismetProceduralMeshLibrary::CalculateTangentsForMesh(Vertices, Triangles, UVCoords, Normals, Tangents);

	MeshComponent->CreateMeshSection(0, Vertices, Triangles, Normals, UVCoords, TArray<FColor>(), Tangents, true);

	

	UE_LOG(LogTemp, Warning, TEXT("Vertices Count: %i | UVCoords Count: %i | Triangles Count: %i"), Vertices.Num(), UVCoords.Num(), Triangles.Num())

	if (AIManager)
	{
		AIManager->GenerateNodes(Vertices, Width, Height);
	}

	//This section will check if it the season we've chosen and then randomly generate the terrain based on that season
	if (WinterManager && !SummerManager && !SpringManager) //if we chose a winter terrain
	{
		MeshComponent->SetMaterial(0, SnowMaterial); //change the material of the mesh we made from the labs to the snow material 
		WinterManager->GenerateTrees(Vertices, Width, Height); //generate random number of trees and houses and its location based on the vertices array, width and height of the mesh component
		
	}

    if (SummerManager && !WinterManager && !SpringManager) //if we chose a summer terrain 
	{
		
		MeshComponent->SetMaterial(0, SandMaterial); //change the material of the mesh we made from the labs to the sand material, which will look like some sort of a beach
		SummerManager->GenerateShrubs(Vertices, Width, Height); //generate random number of shrubs and houses and its location based on the vertices array, width and height of the mesh component
	
	}
	 if (SpringManager && !WinterManager && !SummerManager) //if we chose a spring terrain 
	{
		MeshComponent->SetMaterial(0, SakuraMaterial); //change the material of the mesh we made from the labs to the sakura material, which will look like some sort of a beach
		SpringManager->GenerateSakuraTrees(Vertices, Width, Height); //generate random number of trees and houses and its location based on the vertices array, width and height of the mesh component
	}

}

void AProcedurallyGeneratedMap::ClearMap()
{
	Triangles.Empty();
	Vertices.Empty();
	UVCoords.Empty();
	MeshComponent->ClearAllMeshSections();
	
	//Gets rid of all the static meshes in the level editor before we regenerate a new map by iterating through every one of them in the world and then destroy them 
		for (TActorIterator<AGrassShrub> It(GetWorld()); It; ++It)
		{
			(*It)->Destroy();
		
		}
		
		for (TActorIterator<ATree> It(GetWorld()); It; ++It)
		{
			(*It)->Destroy();
			
		}
		
		for (TActorIterator<ASakuraTree> It(GetWorld()); It; ++It)
		{
			(*It)->Destroy();
			
		}
		
		
		for (TActorIterator<AHouse> It(GetWorld()); It; ++It)
		{
			(*It)->Destroy();

		}
	NewEffect = nullptr; //deactivates the particle system as we clear the map
}

