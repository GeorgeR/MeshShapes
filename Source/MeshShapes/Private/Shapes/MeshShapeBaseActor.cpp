#include "MeshShapeBaseActor.h"
#include "MeshShapeBaseComponent.h"

AMeshShapeBaseActor::AMeshShapeBaseActor()
{
	PrimaryActorTick.bCanEverTick = true;

	//RootComponent = CreateDefaultSubobject<UMeshShapeBaseComponent>(TEXT("Root"));
}

AMSCircleActor::AMSCircleActor()
{
	RootComponent = Shape = CreateDefaultSubobject<UMSCircleComponent>(TEXT("Shape"));
}

AMSNGonActor::AMSNGonActor()
{
	RootComponent = Shape = CreateDefaultSubobject<UMSNGonComponent>(TEXT("Shape"));
}

AMSPolygonActor::AMSPolygonActor()
{
	RootComponent = Shape = CreateDefaultSubobject<UMSPolygonComponent>(TEXT("Shape"));
}

AMSRectangleActor::AMSRectangleActor()
{
	RootComponent = Shape = CreateDefaultSubobject<UMSRectangleComponent>(TEXT("Shape"));
}

AMSSquareActor::AMSSquareActor()
{
	RootComponent = Shape = CreateDefaultSubobject<UMSSquareComponent>(TEXT("Squad"));
}

#if WITH_EDITOR
bool AMeshShapeBaseActor::GetReferencedContentObjects(TArray<UObject *>& Objects) const
{
	Super::GetReferencedContentObjects(Objects);

	UMeshShapeBaseComponent* MeshShape = GetShapeComponent();
	Objects.Add(MeshShape->FillMesh);
	Objects.Add(MeshShape->StrokeMesh);

	if (MeshShape->Fill.Material != nullptr)
		Objects.Add(MeshShape->Fill.Material);

	if (MeshShape->Stroke.Material != nullptr)
		Objects.Add(MeshShape->Stroke.Material);

	return true;
}
#endif