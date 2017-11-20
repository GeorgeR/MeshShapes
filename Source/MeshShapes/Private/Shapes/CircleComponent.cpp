#include "CircleComponent.h"
#include "MeshShapeFunctionLibrary.h"

UMSCircleComponent::UMSCircleComponent()
{
	Radius = 100.0f;
	Segments = 128;
}

void UMSCircleComponent::Update()
{
	Super::Update();

	FillMesh->ClearMeshSection(0);
	StrokeMesh->ClearMeshSection(0);

	FMeshData FillMeshData;
	if (Fill.bEnabled)
	{
		UMeshShapeFunctionLibrary::CreateCircle(Radius, Segments, FillMeshData);

		FillMeshData.CreateMeshSection(FillMesh);
		if(Fill.Material != nullptr) FillMesh->SetMaterial(0, Fill.Material);
	}

	if (Stroke.bEnabled)
	{
		TArray<FVector> StrokePathVertices;
		if (Fill.bEnabled)
			StrokePathVertices = FillMeshData.Vertices;
		else
			UMeshShapeFunctionLibrary::CreateCircleVertices(Radius, Segments, StrokePathVertices);

		StrokePathVertices.RemoveAt(0, 1, true);

		FMeshData StrokeMeshData;
		UMeshShapeFunctionLibrary::StrokePath(StrokePathVertices, Stroke.Thickness, true, StrokeMeshData);
		StrokeMeshData.CreateMeshSection(StrokeMesh);
	}
}