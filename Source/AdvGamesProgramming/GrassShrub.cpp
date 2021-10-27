// Fill out your copyright notice in the Description page of Project Settings.


#include "GrassShrub.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "HealthComponent.h"
#include "Components/InputComponent.h"

// Sets default values
AGrassShrub::AGrassShrub()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Initialise the grass shrub 
	GrassShrub = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Grass Shrub"));
	GrassShrub->SetupAttachment(GetRootComponent());

	//set the shape of the shrub
	//Use the constructor helper to find the default sphere mesh from the engine so that we can access it via code
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShrubAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	GrassShrub->SetStaticMesh(ShrubAsset.Object); //set the shrub to a sphere mesh so that it looks like some sort of animated shrub

	//Use the constructor helper to find the grass material from the engine so that we can access it via code
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> GrassMaterial(TEXT("MaterialInstanceConstant'/Game/Materials/PCGMaterials/Summer/GrassMaterial_Inst.GrassMaterial_Inst'"));
	GrassShrub->SetMaterial(0, GrassMaterial.Object); //set the material of the shrub to the grass material so that it looks like it has grass in it 

	//Set the Z of the relative location so that it looks like it is sat on the mesh component 
	GrassShrub->SetRelativeLocation(FVector(0, 0, -100));

	//set a random scale
	RandomScale = FMath::RandRange(1, 4);
	GrassShrub->SetRelativeScale3D(FVector(RandomScale, RandomScale, RandomScale)); 

}

// Called when the game starts or when spawned
void AGrassShrub::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGrassShrub::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

