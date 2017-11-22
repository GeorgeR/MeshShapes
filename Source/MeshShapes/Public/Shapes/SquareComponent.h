#pragma once

#include "CoreMinimal.h"
#include "Shapes/MeshShapeBaseComponent.h"

#include "SquareComponent.generated.h"

UCLASS(BlueprintType, meta = (BlueprintSpawnableComponent))
class MESHSHAPES_API UMSSquareComponent 
	: public UMeshShapeBaseComponent
{
	GENERATED_BODY()
	
public:
	UMSSquareComponent();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Shape")
	float Size;

	virtual void Update() override;
};