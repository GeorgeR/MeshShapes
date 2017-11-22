#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MeshData.h"

#include "MeshShapeFunctionLibrary.generated.h"

UENUM(BlueprintType)
enum class ETriangulationMethod : uint8
{
	Grid = 0,
	Fan = 1,
	EarClipping = 2
};

UCLASS(BlueprintType)
class MESHSHAPES_API UMeshShapeFunctionLibrary 
	: public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "MeshShapes")
	static void CreateCircle(float InRadius, int32 InSegments, FMeshData& OutData);

	UFUNCTION(BlueprintCallable, Category = "MeshShapes")
	static void CreateCircleVertices(float InRadius, int32 InSegments, TArray<FVector>& OutVertices);

	UFUNCTION(BlueprintCallable, Category = "MeshShapes")
	static void UpdateCircle(float InRadius, FMeshData& InOutData);

	UFUNCTION(BlueprintCallable, Category = "MeshShapes")
	static void CreateArc(float InRadius, int32 InSegments, float InStartAngle, float InEndAngle, bool bWedge, FMeshData& OutData);

	UFUNCTION(BlueprintCallable, Category = "MeshShapes")
	static void CreateArcVertices(float InRadius, int32 InSegments, float InStartAngle, float InEndAngle, TArray<FVector>& OutVertices);

	UFUNCTION(BlueprintCallable, Category = "MeshShapes")
	static void CreateRectangle(float InWidth, float InHeight, FMeshData& OutData);

	UFUNCTION(BlueprintCallable, Category = "MeshShapes")
	static void CreateRectangleVertices(float InWidth, float InHeight, TArray<FVector>& OutVertices);

	UFUNCTION(BlueprintCallable, Category = "MeshShapes")
	static void UpdateRectangle(float InWidth, float InHeight, FMeshData& InOutData);

	UFUNCTION(BlueprintCallable, Category = "MeshShapes")
	static void CreatePolygon(TArray<FVector> InVertices, FMeshData& OutData);

	UFUNCTION(BlueprintCallable, Category = "MeshShapes")
	static void StrokePath(TArray<FVector>& InPoints, float& InThickness, bool bClosed, FMeshData& OutData);

	UFUNCTION(BlueprintCallable, Category = "MeshShapes")
	static void Triangulate(FMeshData& InOutData, ETriangulationMethod InMethod, bool bClosed = false, bool bFlip = false);

private:
	static FVector LineLineIntersect(FVector InA, FVector InVecA, FVector InB, FVector InVecB);
};