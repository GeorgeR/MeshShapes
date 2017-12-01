#include "MeshShapeBaseComponent.h"
#include "UObject/ConstructorHelpers.h"

UMeshShapeBaseComponent::UMeshShapeBaseComponent()
{
	bCollision = false;

	FillMesh = CreateDefaultSubobject<URuntimeMeshComponent>(TEXT("FillMesh"));
	FillMesh->SetupAttachment(this);

	StrokeMesh = CreateDefaultSubobject<URuntimeMeshComponent>(TEXT("StrokeMesh"));
	StrokeMesh->SetupAttachment(this);
	StrokeMesh->AddLocalOffset(FVector(0, 0, 1));

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialObject(TEXT("Material'/MeshShapes/M_Solid.M_Solid'"));
	SolidMaterial = MaterialObject.Object;

	Fill.bEnabled = true;
	Fill.Color = FLinearColor::White;

	Stroke.bEnabled = true;
	Stroke.Color = FLinearColor::Black;
	Stroke.Thickness = 10.0f;
}

void UMeshShapeBaseComponent::Update()
{
	// This causes a serialization issue
	//if(Fill.Material == nullptr)
	//	Fill.Material = UMaterialInstanceDynamic::Create(SolidMaterial, this);

	//UMaterialInstanceDynamic* FillMaterial = Cast<UMaterialInstanceDynamic>(Fill.Material);
	//if(FillMaterial != nullptr)
	//	FillMaterial->SetVectorParameterValue(TEXT("Color"), Fill.Color);

	//if(Stroke.Material == nullptr)
	//	Stroke.Material = UMaterialInstanceDynamic::Create(SolidMaterial, this);

	//UMaterialInstanceDynamic* StrokeMaterial = Cast<UMaterialInstanceDynamic>(Stroke.Material);
	//if(StrokeMaterial != nullptr)
	//	StrokeMaterial->SetVectorParameterValue(TEXT("Color"), Stroke.Color);
}

void UMeshShapeBaseComponent::PostInitProperties()
{
	Super::PostInitProperties();

	Update();
}

#if WITH_EDITOR
void UMeshShapeBaseComponent::PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent)
{
	Super::PostEditChangeChainProperty(PropertyChangedEvent);

	Update();
}

void UMeshShapeBaseComponent::PostEditComponentMove(bool bFinished)
{
	Super::PostEditComponentMove(bFinished);

	Update();
}
#endif