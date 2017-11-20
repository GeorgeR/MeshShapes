#include "RectangleComponent.h"
#include "MeshShapeFunctionLibrary.h"

UMSRectangleComponent::UMSRectangleComponent()
{
	Width = 100.0f;
	Height = 50.0f;
}

void UMSRectangleComponent::Update()
{
	Super::Update();

	FillMesh->ClearMeshSection(0);
	StrokeMesh->ClearMeshSection(0);

	FMeshData FillMeshData;
	if (Fill.bEnabled)
	{
		UMeshShapeFunctionLibrary::CreateRectangle(Width, Height, FillMeshData);

		FillMeshData.CreateMeshSection(FillMesh);
		if (Fill.Material != nullptr) FillMesh->SetMaterial(0, Fill.Material);
	}

	if (Stroke.bEnabled)
	{
		TArray<FVector> StrokePathVertices;
		if (Fill.bEnabled)
			StrokePathVertices = FillMeshData.Vertices;
		else
			UMeshShapeFunctionLibrary::CreateRectangleVertices(Width, Height, StrokePathVertices);

		FVector Temp = StrokePathVertices[2];
		StrokePathVertices[2] = StrokePathVertices[3];
		StrokePathVertices[3] = Temp;

		FMeshData StrokeMeshData;
		UMeshShapeFunctionLibrary::StrokePath(StrokePathVertices, Stroke.Thickness, true, StrokeMeshData);
		StrokeMeshData.CreateMeshSection(StrokeMesh);
	}
}