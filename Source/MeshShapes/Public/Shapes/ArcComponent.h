#pragma once

#include "CoreMinimal.h"
#include "Shapes/MeshShapeBaseComponent.h"

#include "ArcComponent.generated.h"

UCLASS(BlueprintType, meta = (BlueprintSpawnableComponent))
class MESHSHAPES_API UMSArcComponent
	: public UMeshShapeBaseComponent
{
	GENERATED_BODY()
	
public:
	UMSArcComponent();
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Shape")
	float Radius;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Shape")
	int32 Segments;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Shape")
	float StartAngle;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Shape")
	float EndAngle;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Shape")
	bool bWedge;

	virtual void Update() override;
};