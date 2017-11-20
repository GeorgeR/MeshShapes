#pragma once

#include "CoreMinimal.h"
#include "Shapes/MeshShapeBaseComponent.h"

#include "NGonComponent.generated.h"

UCLASS(BlueprintType)
class MESHSHAPES_API UMSNGonComponent 
	: public UMeshShapeBaseComponent
{
	GENERATED_BODY()
	
public:
	UMSNGonComponent();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Shape")
	float Radius;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Shape")
	int32 Sides;

	virtual void Update() override;
};