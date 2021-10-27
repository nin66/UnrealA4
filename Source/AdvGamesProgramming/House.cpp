// Fill out your copyright notice in the Description page of Project Settings.


#include "House.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "Components/InputComponent.h"

// Sets default values
AHouse::AHouse()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Use the constructor helper to find the rock material from the engine so that we can access it via code for both the house and roof 
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> RockMaterial(TEXT("MaterialInstanceConstant'/Game/Materials/PCGMaterials/RockMaterial_Inst.RockMaterial_Inst'"));

	//Initialise the house mesh
	House = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("House"));
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	House->AttachTo(RootComponent);

	//set the shape of the house
	//Use the constructor helper to find the default sphere mesh from the engine so that we can access it via code
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Cube(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	House->SetStaticMesh(Cube.Object);
	//set the material of the house to be rock 
	House->SetMaterial(0, RockMaterial.Object);
	//set a random scale 
	RandomScale = FMath::RandRange(1, 4);
	House->SetRelativeScale3D(FVector(RandomScale, RandomScale, RandomScale)); //apply it for all the coordinates 
	//set their rotation to be zero
	House->SetRelativeRotation(FRotator(0, 0, 0));
	//set the z component of the location so that it looks like it is sitting on the terrain 
	House->SetRelativeLocation(FVector(0, 0, -100));

	//Initialise the roof mesh
	HouseRoof = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("House Roof"));
	HouseRoof->AttachTo(House); //attach the roof to the house 
	//Use the constructor helper to find the default cone mesh from the engine so that we can access it via code
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Cone(TEXT("StaticMesh'/Engine/BasicShapes/Cone.Cone'"));
	HouseRoof->SetStaticMesh(Cone.Object); //make the roof to look like a cone 
	HouseRoof->SetMaterial(0, RockMaterial.Object); //set the material of the roof to be the same as the house 
	HouseRoof->SetRelativeLocation(FVector(0, 0, 100)); //set its relative location so that the roof is always just above the house  
}

// Called when the game starts or when spawned
void AHouse::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHouse::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

