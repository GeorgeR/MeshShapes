#include "MSArrowComponent.h"
#include "MeshShapeFunctionLibrary.h"

UMSArrowComponent::UMSArrowComponent()
{
	TailWidth = 20.0f;
	TailHeight = 100.0f;
	HeadWidth = 100.0f;
	HeadHeight = 100.0f;
	HeadOffset = -20.0f;
}

void UMSArrowComponent::Update()
{
	Super::Update();

	FillMesh->ClearMeshSection(0);
	StrokeMesh->ClearMeshSection(0);

	TArray<FVector> Vertices;
	if (Fill.bEnabled || Stroke.bEnabled)
	{
		float HalfTailWidth = TailWidth * 0.5f;
		float HalfHeadWidth = HeadWidth * 0.5f;

		Vertices.Add(FVector(-HalfTailWidth, -TailHeight, 0.0f));
		Vertices.Add(FVector(-HalfTailWidth, 0.0f, 0.0f));
		Vertices.Add(FVector(-HalfHeadWidth, HeadOffset, 0.0f));
		Vertices.Add(FVector(0.0f, HeadHeight, 0.0f));
		Vertices.Add(FVector(+HalfHeadWidth, HeadOffset, 0.0f));
		Vertices.Add(FVector(+HalfTailWidth, 0.0f, 0.0f));
		Vertices.Add(FVector(+HalfTailWidth, -TailHeight, 0.0f));
	}

	if (Fill.bEnabled)
	{
		FMeshData FillMeshData;

		TArray<int32> Indices;

		Indices.Add(0);
		Indices.Add(1);
		Indices.Add(5);

		Indices.Add(5);
		Indices.Add(6);
		Indices.Add(0);

		Indices.Add(3);
		Indices.Add(1);
		Indices.Add(2);

		Indices.Add(3);
		Indices.Add(5);
		Indices.Add(1);

		Indices.Add(3);
		Indices.Add(4);
		Indices.Add(5);

		FillMeshData.Vertices = Vertices;
		FillMeshData.Indices = Indices;
		FillMeshData.Fill(Vertices.Num());

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