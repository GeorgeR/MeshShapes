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

	if (Points.Num() <= 1)
		return;

	FMeshData FillMeshData;
	if (Fill.bEnabled && bClosed && Points.Num() > 2)
	{
		UMeshShapeFunctionLibrary::CreatePolygon(Points, FillMeshData);
		
		FillMeshData.CreateMeshSection(FillMesh);
		if (Fill.Material != nullptr) FillMesh->SetMaterial(0, Fill.Material);
	}

	if (Stroke.bEnabled && Points.Num() > 1)
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