// Fill out your copyright notice in the Description page of Project Settings.


#include "BakeDynamicToStaticMesh.h"

#include "AssetRegistry/AssetRegistryModule.h"

// Sets default values for this component's properties
UBakeDynamicToStaticMesh::UBakeDynamicToStaticMesh()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBakeDynamicToStaticMesh::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBakeDynamicToStaticMesh::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

UStaticMesh*  UBakeDynamicToStaticMesh::BakeStaticMesh(UStaticMeshDescription* Description, TArray<UMaterialInterface*> Materials, FString name)
{
	FString Path = FString(TEXT("/Game/Snow_Meshes/"));
	FString MeshName = FString(TEXT("SM_") + name);
	FString PackageName = Path + MeshName;
	UPackage* Package = CreatePackage(*PackageName);
	UStaticMesh* StaticMesh = NewObject<UStaticMesh>(Package, FName(*MeshName), RF_Public | RF_Standalone);
	
	StaticMesh->bAllowCPUAccess = true;
	StaticMesh->NeverStream = true;
	StaticMesh->InitResources();
	StaticMesh->SetLightingGuid();

	for (int i = 0; i < Materials.Num(); i++)
	{
		StaticMesh->GetStaticMaterials().Add(FStaticMaterial(Materials[i]));
	}

#if WITH_EDITOR

	StaticMesh->PostEditChange();

#endif
	StaticMesh->MarkPackageDirty();

	FAssetRegistryModule::AssetCreated(StaticMesh);

	return StaticMesh;

}

