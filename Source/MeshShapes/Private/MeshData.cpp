#include "MeshData.h"

void FMeshData::Fill(int32 Count)
{
	Vertices.Init(FVector::ZeroVector, Count);
	Indices.Init(0, Count);
	Normals.Init(FVector::UpVector, Count);
	UVs.Init(FVector2D::ZeroVector, Count);
	Colors.Init(FColor::White, Count);
	Tangents.Init(FRuntimeMeshTangent(), Count);
}

void FMeshData::CreateMeshSection(URuntimeMeshComponent* InMesh, int32 InSection, bool bCreateCollision, EUpdateFrequency InUpdateFrequency)
{
	InMesh->CreateMeshSection(InSection, Vertices, Indices, Normals, UVs, Colors, Tangents, bCreateCollision, InUpdateFrequency);
}

void FMeshData::UpdateMeshSection(URuntimeMeshComponent* InMesh, int32 InSection, ESectionUpdateFlags InUpdateFlags)
{
	// TODO
	//InMesh->UpdateMeshSection<FVector>(InSection, Vertices, Indices, Normals, UVs, Colors, Tangents, InUpdateFlags);
}