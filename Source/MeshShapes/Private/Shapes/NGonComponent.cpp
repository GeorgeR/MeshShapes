#include "NGonComponent.h"
#include "MeshShapeFunctionLibrary.h"

UMSNGonComponent::UMSNGonComponent()
{
	Radius = 100.0f;
	Sides = 5;
}

void UMSNGonComponent::Update()
{
	Super::Update();

	FillMesh->ClearMeshSection(0);
	StrokeMesh->ClearMeshSection(0);

	FMeshData FillMeshData;
	if (Fill.bEnabled)
	{
		UMeshShapeFunctionLibrary::CreateCircle(Radius, Sides, FillMeshData);

		FillMeshData.CreateMeshSection(FillMesh);
		if (Fill.Material != nullptr) FillMesh->SetMaterial(0, Fill.Material);
	}

	if (Stroke.bEnabled)
	{
		TArray<FVector> StrokePathVertices;
		if (Fill.bEnabled)
			StrokePathVertices = FillMeshData.Vertices;
		else
			UMeshShapeFunctionLibrary::CreateCircleVertices(Radius, Sides, StrokePathVertices);

		StrokePathVertices.RemoveAt(0, 1, true);

		FMeshData StrokeMeshData;
		UMeshShapeFunctionLibrary::StrokePath(StrokePathVertices, Stroke.Thickness, true, StrokeMeshData);
		StrokeMeshData.CreateMeshSection(StrokeMesh);
	}
}