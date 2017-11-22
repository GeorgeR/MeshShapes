#pragma once

#include "CoreMinimal.h"
#include "Shapes/MeshShapeBaseComponent.h"

#include "PolygonComponent.generated.h"

UCLASS(BlueprintType, meta = (BlueprintSpawnableComponent))
class MESHSHAPES_API UMSPolygonComponent 
	: public UMeshShapeBaseComponent
{
	GENERATED_BODY()
	
public:
	UMSPolygonComponent();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Shape")
	TArray<FVector> Points;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Shape")
	bool bClosed;

	virtual void Update() override;
};