// Fill out your copyright notice in the Description page of Project Settings.


#include "Tree.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "Components/InputComponent.h"


// Sets default values
ATree::ATree()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Initialise the tree mesh
	Tree = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tree"));
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	Tree->AttachTo(RootComponent);

	//set the shape of the tree
	//Use the constructor helper to find the default cylinder mesh from the engine so that we can access it via code
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CylinderAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cylinder.Cylinder'"));
	Tree->SetStaticMesh(CylinderAsset.Object); //set the tree to a cylinder mesh so that it looks like a tree log

	//set a random height
	RandomHeight = FMath::FRandRange(4.0, 8.0); //initialise the random height float to a range between 4 and 8 so that it changes the height of the tree
	Tree->SetRelativeScale3D(FVector(1.0, 1.0, RandomHeight)); //randomizes the height of the tree 

	//Use the constructor helper to find the tree material from the engine so that we can access it via code
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> TreeMaterial(TEXT("MaterialInstanceConstant'/Game/Materials/PCGMaterials/TreeMaterial_Inst.TreeMaterial_Inst'"));
	Tree->SetMaterial(0, TreeMaterial.Object); //set the material of the tree to the tree material so that it has the colour of a tree log with snow on top 

	
}

// Called when the game starts or when spawned
void ATree::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATree::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}




