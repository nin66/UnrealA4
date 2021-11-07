// Fill out your copyright notice in the Description page of Project Settings.


#include "AutumnTree.h"
#include "DrawDebugHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"


AAutumnTree::AAutumnTree()
{
	TreeLeaves = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tree Leaves"));
	TreeLeaves->AttachTo(Tree); //attach the leaves to the tree 

	//set the leaves as a sphere 
	static ConstructorHelpers::FObjectFinder<UStaticMesh> LeavesAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	TreeLeaves->SetStaticMesh(LeavesAsset.Object);

	//add the autumn material to the leaves so that the leaves are orangish colour
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> AutumnMaterial(TEXT("MaterialInstanceConstant'/Game/Materials/PCGMaterials/Autumn/AutumnLandScapeMaterial_Inst.AutumnLandScapeMaterial_Inst'"));
	TreeLeaves->SetMaterial(0, AutumnMaterial.Object);

	//set the location of the leaves so that it is right above the tree log 
	TreeLeaves->SetRelativeLocation(FVector(0, 0, 60));

	//set the scale of the leaves so that it remains constant throughout 
	TreeLeaves->SetRelativeScale3D(FVector(2.5, 2, 0.5));
}