#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RuntimeMeshComponent.h"

#include "MeshData.generated.h"

USTRUCT(BlueprintType)
struct MESHSHAPES_API FMeshData
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly)
	TArray<FVector> Vertices;
	
	UPROPERTY(BlueprintReadOnly)
	TArray<int32> Indices;

	UPROPERTY(BlueprintReadOnly)
	TArray<FVector> Normals;

	UPROPERTY(BlueprintReadOnly)
	TArray<FVector2D> UVs;

	UPROPERTY(BlueprintReadOnly)
	TArray<FColor> Colors;

	TArray<FRuntimeMeshTangent> Tangents;

	void Fill(int32 Count);

	void CreateMeshSection(URuntimeMeshComponent* InMesh, int32 InSection, bool bCreateCollision = false, EUpdateFrequency InUpdateFrequency = EUpdateFrequency::Infrequent);
	void UpdateMeshSection(URuntimeMeshComponent* InMesh, int32 InSection, ESectionUpdateFlags InUpdateFlags);
};