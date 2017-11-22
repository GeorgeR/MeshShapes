#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RuntimeMeshComponent.h"

#include "CircleComponent.h"
#include "NGonComponent.h"
#include "PolygonComponent.h"
#include "RectangleComponent.h"
#include "SquareComponent.h"

#include "MeshShapeBaseActor.generated.h"

UCLASS(Abstract, HideCategories = (Input, HLOD))
class MESHSHAPES_API AMeshShapeBaseActor 
	: public AActor
{
	GENERATED_BODY()
	
public:
	AMeshShapeBaseActor();

#if WITH_EDITOR
	virtual bool GetReferencedContentObjects(TArray<UObject *>& Objects) const override;
#endif

	virtual UMeshShapeBaseComponent* GetShapeComponent() const { return nullptr; }
};

UCLASS(BlueprintType, ComponentWrapperClass)
class MESHSHAPES_API AMSCircleActor
	: public AMeshShapeBaseActor
{
	GENERATED_BODY()

public:
	AMSCircleActor();

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UMSCircleComponent* Shape;

	inline virtual UMeshShapeBaseComponent* GetShapeComponent() const { return Shape; }
};

UCLASS(BlueprintType)
class MESHSHAPES_API AMSNGonActor
	: public AMeshShapeBaseActor
{
	GENERATED_BODY()

public:
	AMSNGonActor();

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UMSNGonComponent* Shape;

	inline virtual UMeshShapeBaseComponent* GetShapeComponent() const { return Shape; }
};

UCLASS(BlueprintType)
class MESHSHAPES_API AMSPolygonActor
	: public AMeshShapeBaseActor
{
	GENERATED_BODY()

public:
	AMSPolygonActor();

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UMSPolygonComponent* Shape;

	inline virtual UMeshShapeBaseComponent* GetShapeComponent() const { return Shape; }
};

UCLASS(BlueprintType)
class MESHSHAPES_API AMSRectangleActor
	: public AMeshShapeBaseActor
{
	GENERATED_BODY()

public:
	AMSRectangleActor();

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UMSRectangleComponent* Shape;

	inline virtual UMeshShapeBaseComponent* GetShapeComponent() const { return Shape; }
};

UCLASS(BlueprintType)
class MESHSHAPES_API AMSSquareActor
	: public AMeshShapeBaseActor
{
	GENERATED_BODY()

public:
	AMSSquareActor();

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UMSSquareComponent* Shape;

	inline virtual UMeshShapeBaseComponent* GetShapeComponent() const { return Shape; }
};