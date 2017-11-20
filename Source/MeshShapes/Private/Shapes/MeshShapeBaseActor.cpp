#include "MeshShapeBaseActor.h"
#include "MeshShapeBaseComponent.h"

AMeshShapeBaseActor::AMeshShapeBaseActor()
{
	PrimaryActorTick.bCanEverTick = true;

	//RootComponent = CreateDefaultSubobject<UMeshShapeBaseComponent>(TEXT("Root"));
}

AMSCircleActor::AMSCircleActor()
{
	RootComponent = CreateDefaultSubobject<UMSCircleComponent>(TEXT("Shape"));
}

AMSNGonActor::AMSNGonActor()
{
	RootComponent = CreateDefaultSubobject<UMSNGonComponent>(TEXT("Shape"));
}

AMSPolygonActor::AMSPolygonActor()
{
	RootComponent = CreateDefaultSubobject<UMSPolygonComponent>(TEXT("Shape"));
}

AMSRectangleActor::AMSRectangleActor()
{
	RootComponent = CreateDefaultSubobject<UMSRectangleComponent>(TEXT("Shape"));
}

AMSSquareActor::AMSSquareActor()
{
	RootComponent = CreateDefaultSubobject<UMSSquareComponent>(TEXT("Squad"));
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