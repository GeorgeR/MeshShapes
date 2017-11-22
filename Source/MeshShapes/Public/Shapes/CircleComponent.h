#pragma once

#include "CoreMinimal.h"
#include "MeshShapeBaseComponent.h"

#include "CircleComponent.generated.h"

UCLASS(BlueprintType, meta = (BlueprintSpawnableComponent))
class MESHSHAPES_API UMSCircleComponent 
	: public UMeshShapeBaseComponent
{
	GENERATED_BODY()

public:
	UMSCircleComponent();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Shape")
	float Radius;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Shape")
	int32 Segments;

	virtual void Update() override;
};