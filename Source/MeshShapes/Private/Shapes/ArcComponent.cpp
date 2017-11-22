#include "ArcComponent.h"
#include "MeshShapeFunctionLibrary.h"

UMSArcComponent::UMSArcComponent()
{
	Radius = 100.0f;
	Segments = 64;
	StartAngle = 45.0f;
	EndAngle = 135.0f;
	bWedge = false;
}

void UMSArcComponent::Update()
{
	Super::Update();

	if (StartAngle > EndAngle)
	{
		float Temp = StartAngle;
		StartAngle = EndAngle;
		EndAngle = Temp;
	}

	FillMesh->ClearMeshSection(0);
	StrokeMesh->ClearMeshSection(0);

	FMeshData FillMeshData;
	if (Fill.bEnabled)
	{
		UMeshShapeFunctionLibrary::CreateArc(Radius, Segments, StartAngle, EndAngle, bWedge, FillMeshData);

	}
}