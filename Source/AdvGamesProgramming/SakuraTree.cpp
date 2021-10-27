// Fill out your copyright notice in the Description page of Project Settings.


#include "SakuraTree.h"
#include "DrawDebugHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "Components/InputComponent.h"
// Sets default values
ASakuraTree::ASakuraTree()
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

	//set a random height - same as tree.cpp
	RandomHeight = FMath::FRandRange(4.0, 8.0);
	Tree->SetRelativeScale3D(FVector(1.0, 1.0, RandomHeight));

	//set the material - same as tree.cpp 
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> TreeMaterial(TEXT("MaterialInstanceConstant'/Game/Materials/PCGMaterials/TreeMaterial_Inst.TreeMaterial_Inst'"));
	Tree->SetMaterial(0, TreeMaterial.Object);

	//initialize the tree leaves mesh 
	TreeLeaves = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tree Leaves"));
	TreeLeaves->AttachTo(Tree); //attach the leaves to the tree 

	//set the leaves to form a sphere 
	static ConstructorHelpers::FObjectFinder<UStaticMesh> LeavesAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
    TreeLeaves->SetStaticMesh(LeavesAsset.Object);

	//add the sakura material to the leaves so that the leaves are pink 
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> SakuraMaterial(TEXT("MaterialInstanceConstant'/Game/Materials/PCGMaterials/Spring/SakuraMaterial_Inst.SakuraMaterial_Inst'"));
	TreeLeaves->SetMaterial(0, SakuraMaterial.Object);

	//set the location of the leaves so that it is right above the tree log 
	TreeLeaves->SetRelativeLocation(FVector(0, 0, 60));

	//set the scale of the leaves so that it remains constant throughout 
	TreeLeaves->SetRelativeScale3D(FVector(2.5, 2, 0.5));
}

// Called when the game starts or when spawned
void ASakuraTree::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASakuraTree::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

