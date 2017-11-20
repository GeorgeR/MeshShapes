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

	FMeshData FillMeshData;
	if (Fill.bEnabled)
	{
		
		UMeshShapeFunctionLibrary::CreateCircle(Radius, Segments, FillMeshData);
		
		FillMeshData.CreateMeshSection(FillMesh, 0);
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

		for (auto i = 0; i < StrokeMeshData.Vertices.Num(); i++)
			DrawDebugSphere(GetWorld(), StrokeMeshData.Vertices[i], 1.0f, 16, FColor::Red, false, 50.0f);
	}
}