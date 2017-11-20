#include "SquareComponent.h"
#include "MeshShapeFunctionLibrary.h"

UMSSquareComponent::UMSSquareComponent()
{
	Size = 100.0f;
}

void UMSSquareComponent::Update()
{
	Super::Update();

	FillMesh->ClearMeshSection(0);
	StrokeMesh->ClearMeshSection(0);

	FMeshData FillMeshData;
	if (Fill.bEnabled)
	{
		UMeshShapeFunctionLibrary::CreateRectangle(Size, Size, FillMeshData);

		FillMeshData.CreateMeshSection(FillMesh);
		if (Fill.Material != nullptr) FillMesh->SetMaterial(0, Fill.Material);
	}

	if (Stroke.bEnabled)
	{
		TArray<FVector> StrokePathVertices;
		if (Fill.bEnabled)
			StrokePathVertices = FillMeshData.Vertices;
		else
			UMeshShapeFunctionLibrary::CreateRectangleVertices(Size, Size, StrokePathVertices);

		FVector Temp = StrokePathVertices[2];
		StrokePathVertices[2] = StrokePathVertices[3];
		StrokePathVertices[3] = Temp;

		FMeshData StrokeMeshData;
		UMeshShapeFunctionLibrary::StrokePath(StrokePathVertices, Stroke.Thickness, true, StrokeMeshData);
		StrokeMeshData.CreateMeshSection(StrokeMesh);
	}
}