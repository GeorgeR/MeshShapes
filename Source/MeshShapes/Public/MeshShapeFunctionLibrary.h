#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "MeshShapeFunctionLibrary.generated.h"

UCLASS()
class MESHSHAPES_API UMeshShapeFunctionLibrary 
	: public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "MeshShapes")
	static void StrokePath(TArray<FVector>& InPoints, float& InThickness, bool bClosed, TArray<FVector>& OutVertices, TArray<int32>& OutIndices);

private:
	static FVector LineLineIntersect(FVector InA, FVector InVecA, FVector InB, FVector InVecB);
};