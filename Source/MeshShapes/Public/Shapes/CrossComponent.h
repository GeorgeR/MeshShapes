#pragma once

#include "CoreMinimal.h"
#include "Shapes/MeshShapeBaseComponent.h"

#include "CrossComponent.generated.h"

UCLASS(BlueprintType, meta = (BlueprintSpawnableComponent))
class MESHSHAPES_API UMSCrossComponent 
	: public UMeshShapeBaseComponent
{
	GENERATED_BODY()

public:
	UMSCrossComponent();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Shape")
	float Width;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Shape")
	float Height;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Shape")
	float Thickness;

	virtual void Update() override;
};