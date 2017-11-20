#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "RuntimeMeshComponent.h"

#include "MeshShapeBaseComponent.generated.h"

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

UCLASS(ClassGroup=(MeshShape), meta=(BlueprintSpawnableComponent), HideCategories = (Input))
class MESHSHAPES_API UMeshShapeBaseComponent 
	: public USceneComponent
{
	GENERATED_BODY()

public:
	UMeshShapeBaseComponent();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Shape")
	bool bCollision;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Shape")
	FMSBrush Fill;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Shape")
	FMSBrush Stroke;

	virtual void Update();

#if WITH_EDITOR
	virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;
	virtual void PostEditComponentMove(bool bFinished) override;
#endif

	virtual void PostInitProperties() override;

protected:
	friend class AMeshShapeBaseActor;

	UPROPERTY(BlueprintReadOnly)
	URuntimeMeshComponent* FillMesh;

	UPROPERTY(BlueprintReadOnly)
	URuntimeMeshComponent* StrokeMesh;

	UPROPERTY()
	UMaterialInterface* SolidMaterial;
};