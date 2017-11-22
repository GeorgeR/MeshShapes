#pragma once

#include "CoreMinimal.h"
#include "Shapes/MeshShapeBaseComponent.h"

#include "RectangleComponent.generated.h"

UCLASS(BlueprintType, meta = (BlueprintSpawnableComponent))
class MESHSHAPES_API UMSRectangleComponent 
	: public UMeshShapeBaseComponent
{
	GENERATED_BODY()
	
public:
	UMSRectangleComponent();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Shape")
	float Width;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Shape")
	float Height;

	virtual void Update() override;
};