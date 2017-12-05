#pragma once

#include "CoreMinimal.h"
#include "Shapes/MeshShapeBaseComponent.h"

#include "MSArrowComponent.generated.h"

UCLASS(BlueprintType, meta = (BlueprintSpawnableComponent))
class MESHSHAPES_API UMSArrowComponent 
	: public UMeshShapeBaseComponent
{
	GENERATED_BODY()

public:
	UMSArrowComponent();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Shape")
	float TailWidth;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Shape")
	float TailHeight;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Shape")
	float HeadWidth;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Shape")
	float HeadHeight;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Shape")
	float HeadOffset;

	virtual void Update() override;
};