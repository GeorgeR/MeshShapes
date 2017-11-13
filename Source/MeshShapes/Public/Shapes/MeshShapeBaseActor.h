#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RuntimeMeshComponent.h"

#include "MeshShapeBaseActor.generated.h"

USTRUCT(BlueprintType)
struct MESHSHAPES_API FMSBrush
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	bool bEnabled;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UMaterialInterface* Material;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FLinearColor Color;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float Thickness;
};

UCLASS(Abstract, HideCategories = (Input, HLOD))
class MESHSHAPES_API AMeshShapeBaseActor 
	: public AActor
{
	GENERATED_BODY()
	
public:
	AMeshShapeBaseActor();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Shape")
	FMSBrush Fill;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Shape")
	FMSBrush Stroke;

	UPROPERTY(BlueprintReadOnly)
	URuntimeMeshComponent* FillMesh;

	UPROPERTY(BlueprintReadOnly)
	URuntimeMeshComponent* StrokeMesh;

	virtual void Update() { };

	virtual void PostInitProperties() override;

#if WITH_EDITOR
	virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;
#endif
};