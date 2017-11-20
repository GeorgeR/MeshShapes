#include "PolygonComponent.h"
#include "MeshShapeFunctionLibrary.h"

UMSPolygonComponent::UMSPolygonComponent()
{
	Fill.bEnabled = false;

	Points = {
		FVector(0,0,0),
		FVector(100,0,0)
	};

	bClosed = false;
}

void UMSPolygonComponent::Update()
{
	Super::Update();

	FillMesh->ClearMeshSection(0);
	StrokeMesh->ClearMeshSection(0);

	FMeshData FillMeshData;
	if (Fill.bEnabled && bClosed)
	{
		UMeshShapeFunctionLibrary::CreatePolygon(Points, FillMeshData);
		
		FillMeshData.CreateMeshSection(FillMesh);
		if (Fill.Material != nullptr) FillMesh->SetMaterial(0, Fill.Material);
	}

	if (Stroke.bEnabled)
	{
		TArray<FVector> StrokePathVertices;
		if (FillMeshData.Vertices.Num() > 0)
			StrokePathVertices = FillMeshData.Vertices;
		else
			StrokePathVertices = Points;
			
		FMeshData StrokeMeshData;
		UMeshShapeFunctionLibrary::StrokePath(StrokePathVertices, Stroke.Thickness, bClosed, StrokeMeshData);
		StrokeMeshData.CreateMeshSection(StrokeMesh);
	}
}