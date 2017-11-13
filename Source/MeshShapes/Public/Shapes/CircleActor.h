#pragma once

#include "CoreMinimal.h"
#include "Shapes/MeshShapeBaseActor.h"

#include "CircleActor.generated.h"

UCLASS(meta = (DisplayName = "CircleShape"))
class MESHSHAPES_API AMSCircleActor 
	: public AMeshShapeBaseActor
{
	GENERATED_BODY()

public:
	AMSCircleActor();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Shape")
	float Radius;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Shape")
	int32 Segments;

	virtual void Update() override;
};