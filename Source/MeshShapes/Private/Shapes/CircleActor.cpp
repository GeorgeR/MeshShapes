#include "CircleActor.h"

AMSCircleActor::AMSCircleActor()
{
	Radius = 100.0f;
	Segments = 32;
}

void AMSCircleActor::Update()
{
	FillMesh->ClearMeshSection(0);
	StrokeMesh->ClearMeshSection(0);

	if (Fill.bEnabled)
	{
		float Step = 2.0f / Segments;
		TArray<FVector> Vertices;
		Vertices.Add(FVector::ZeroVector);
		for (auto i = 0; i < Segments; i++)
		{
			FVector Vertex; 
			Vertex.X = FMath::Cos(i * Step);
			Vertex.Y = FMath::Sin(i * Step);
			Vertex.Z = 0.0f;
			Vertices.Add(Vertex);
		}

		TArray<int32> Triangles;
		for (auto i = 1; i < Segments; i++)
		{
			Triangles.Add(0);
			Triangles.Add(i);
			Triangles.Add(i + 1);
		}

		TArray<FVector> Normals;
		Normals.Init(FVector::UpVector, Vertices.Num());

		TArray<FVector2D> UVs;
		UVs.Init(FVector2D(0, 1), Vertices.Num());

		TArray<FColor> Colors;
		Colors.Init(FColor::White, Vertices.Num());

		TArray<FRuntimeMeshTangent> Tangents;
		Tangents.Init(FRuntimeMeshTangent(), Vertices.Num());

		FillMesh->CreateMeshSection(0, Vertices, Triangles, Normals, UVs, Colors, Tangents, false, EUpdateFrequency::Infrequent, ESectionUpdateFlags::None);
		if(Fill.Material != nullptr) FillMesh->SetMaterial(0, Fill.Material);
	}

	if (Stroke.bEnabled)
	{

	}
}