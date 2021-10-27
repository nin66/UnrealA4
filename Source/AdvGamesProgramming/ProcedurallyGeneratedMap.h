// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "ProcedurallyGeneratedMap.generated.h"

UCLASS()
class ADVGAMESPROGRAMMING_API AProcedurallyGeneratedMap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProcedurallyGeneratedMap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UPROPERTY(VisibleAnywhere)
	UProceduralMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere)
	int32 Width;
	UPROPERTY(EditAnywhere)
	int32 Height;
	UPROPERTY(EditAnywhere)
	float GridSize;

	UPROPERTY(EditAnywhere)
	float PerlinScale;
	UPROPERTY(EditAnywhere)
	float PerlinRoughness;

	UPROPERTY(EditAnywhere)
	bool bRegenerateMap;

	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector2D> UVCoords;
	TArray<FVector> Normals;
	TArray<FProcMeshTangent> Tangents;

	UPROPERTY(EditAnywhere)
	class AAIManager* AIManager;

	//Managers to generate terrain for each season
	UPROPERTY(EditAnywhere)
		class ATreeManager* WinterManager;    //Winter Manager generates the winter terrain. It is from the tree manager component that initially is used to generate the winter trees (logs). However changing the name of the script is too complicated so I'll leave it here. 

	UPROPERTY(EditAnywhere)
		class AShrubManager* SummerManager; //Summer manager generates the summer terrain. 
	UPROPERTY(EditAnywhere)
		class ASpringManager* SpringManager; //Spring manager generates the spring terrain. 

	//Material interfaces for each season
	UMaterialInterface* SnowMaterial; //Snow material for a snowy surface 
	UMaterialInterface* SandMaterial; //Sand material for a beach-like surface
	UMaterialInterface* SakuraMaterial; //Sakura material with a sakura-filled surface

	//Niagara particle systems for the falling items for each season
	UPROPERTY(EditAnywhere, Category = "Snow")
    class UNiagaraSystem* SnowEffect; //Snow effect to simulate snow

	UPROPERTY(EditAnywhere, Category = "Rain")
	 UNiagaraSystem* RainEffect; //Rain effect to simulate rain

	UPROPERTY(EditAnywhere, Category = "Sakura")
		UNiagaraSystem* SakuraEffect; //Sakura effect to simulate sakura flowers falling

	class UNiagaraComponent* NewEffect; //The niagara component to spawn the niagara systems 
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual bool ShouldTickIfViewportsOnly() const override;

	UFUNCTION(BlueprintCallable)
	void GenerateMap();

	void ClearMap();

};
