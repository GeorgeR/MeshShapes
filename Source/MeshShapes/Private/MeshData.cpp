#include "MeshData.h"

void FMeshData::Fill(int32 Count)
{
	if(Vertices.Num() == 0) Vertices.Init(FVector::ZeroVector, Count);
	if(Indices.Num() == 0) Indices.Init(0, Count);
	if(Normals.Num() == 0) Normals.Init(FVector::UpVector, Count);
	if(UVs.Num() == 0) UVs.Init(FVector2D::ZeroVector, Count);
	if(Colors.Num() == 0) Colors.Init(FColor::White, Count);
	if(Tangents.Num() == 0) Tangents.Init(FRuntimeMeshTangent(), Count);
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