#include "CircleActor.h"
#include "MeshShapeFunctionLibrary.h"

AMSCircleActor::AMSCircleActor()
{
	Radius = 100.0f;
	Segments = 128;
}

void AMSCircleActor::Update()
{
	FillMesh->ClearMeshSection(0);
	StrokeMesh->ClearMeshSection(0);

	TArray<FVector> Vertices;
	if (Fill.bEnabled || Stroke.bEnabled)
	{
		float Step = (PI * 2.0f) / Segments;
		Vertices.Add(FVector::ZeroVector);
		for (auto i = 0; i < Segments; i++)
		{
			FVector Vertex;
			Vertex.X = Radius * FMath::Cos(i * Step);
			Vertex.Y = Radius * FMath::Sin(i * Step);
			Vertex.Z = 0.0f;
			Vertices.Add(Vertex);
		}
	}

	if (Fill.bEnabled)
	{
		TArray<int32> Triangles;
		for (auto i = 1; i < Segments; i++)
		{
			Triangles.Add(0);
			Triangles.Add(i + 1);
			Triangles.Add(i);
		}

		Triangles.Add(0);
		Triangles.Add(1);
		Triangles.Add(Segments);

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
		TArray<FVector> StrokePathVertices = Vertices;
		StrokePathVertices.RemoveAt(0, 1, true);

		TArray<FVector> StrokeVertices;
		TArray<int32> Indices;
		UMeshShapeFunctionLibrary::StrokePath(Vertices, Stroke.Thickness, true, StrokeVertices, Indices);

		for (auto i = 0; i < StrokeVertices.Num(); i++)
			DrawDebugSphere(GetWorld(), StrokeVertices[i], 1.0f, 16, FColor::Red, false, 50.0f);
	}
}