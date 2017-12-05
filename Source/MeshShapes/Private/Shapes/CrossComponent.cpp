#include "CrossComponent.h"
#include "MeshShapeFunctionLibrary.h"

UMSCrossComponent::UMSCrossComponent()
{
	Width = 100.0f;
	Height = 100.0f;
	Thickness = 10.0f;
}

void UMSCrossComponent::Update()
{
	Super::Update();

	FillMesh->ClearMeshSection(0);
	StrokeMesh->ClearMeshSection(0);

	TArray<FVector> Vertices;
	if (Fill.bEnabled || Stroke.bEnabled)
	{
		float HalfWidth = Width * 0.5f;
		float HalfHeight = Height * 0.5f;
		float HalfThickness = Thickness * 0.5f;

		Vertices.Add(FVector(-HalfWidth,		+HalfThickness, 0.0f));	// 0
		Vertices.Add(FVector(-HalfThickness,	+HalfThickness, 0.0f));	// 1
		Vertices.Add(FVector(-HalfThickness,	+HalfHeight,	0.0f)); // 2
		Vertices.Add(FVector(+HalfThickness,	+HalfHeight,	0.0f)); // 3
		Vertices.Add(FVector(+HalfThickness,	+HalfThickness, 0.0f)); // 4
		Vertices.Add(FVector(+HalfWidth,		+HalfThickness, 0.0f)); // 5
		Vertices.Add(FVector(+HalfWidth,		-HalfThickness, 0.0f)); // 6
		Vertices.Add(FVector(+HalfThickness,	-HalfThickness, 0.0f)); // 7
		Vertices.Add(FVector(+HalfThickness,	-HalfHeight,	0.0f)); // 8
		Vertices.Add(FVector(-HalfThickness,	-HalfHeight,	0.0f)); // 9
		Vertices.Add(FVector(-HalfThickness,	-HalfThickness, 0.0f)); // 10
		Vertices.Add(FVector(-HalfWidth,		-HalfThickness, 0.0f)); // 11
	}

	if (Fill.bEnabled)
	{
		FMeshData FillMeshData;

		TArray<int32> Indices;

		Indices.Add(11);
		Indices.Add(0);
		Indices.Add(1);

		Indices.Add(1);
		Indices.Add(10);
		Indices.Add(11);

		Indices.Add(10);
		Indices.Add(1);
		Indices.Add(4);

		Indices.Add(4);
		Indices.Add(7);
		Indices.Add(10);
		
		Indices.Add(1);
		Indices.Add(2);
		Indices.Add(3);

		Indices.Add(3);
		Indices.Add(4);
		Indices.Add(1);

		Indices.Add(7);
		Indices.Add(4);
		Indices.Add(5);

		Indices.Add(5);
		Indices.Add(6);
		Indices.Add(7);

		Indices.Add(9);
		Indices.Add(10);
		Indices.Add(7);

		Indices.Add(7);
		Indices.Add(8);
		Indices.Add(9);

		FillMeshData.Vertices = Vertices;
		FillMeshData.Indices = Indices;
		FillMeshData.Fill(FillMeshData.Vertices.Num());

		FillMeshData.CreateMeshSection(FillMesh);
		if (Fill.Material != nullptr) FillMesh->SetMaterial(0, Fill.Material);
	}

	if (Stroke.bEnabled)
	{
		FMeshData StrokeMeshData;
		UMeshShapeFunctionLibrary::StrokePath(Vertices, Stroke.Thickness, true, StrokeMeshData);
		StrokeMeshData.CreateMeshSection(StrokeMesh);
	}
}