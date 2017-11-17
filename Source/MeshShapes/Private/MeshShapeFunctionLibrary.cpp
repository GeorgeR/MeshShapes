#include "MeshShapeFunctionLibrary.h"

void UMeshShapeFunctionLibrary::StrokePath(TArray<FVector>& InPoints, float& InThickness, bool bClosed /*= true*/, TArray<FVector>& OutVertices, TArray<int32>& OutIndices)
{
	float HalfThickness = InThickness * 0.5f;

	for (auto i = 0; i < InPoints.Num(); i++)
	{
		FVector PreviousPoint = i == 0 ? InPoints[InPoints.Num() - 1] : InPoints[i - 1];
		FVector ThisPoint = InPoints[i];
		FVector NextPoint = i == InPoints.Num() - 1 ? InPoints[0] : InPoints[i + 1];
		
		FVector PreviousDirection = (ThisPoint - PreviousPoint).GetSafeNormal();
		FVector NextDirection = (NextPoint - ThisPoint).GetSafeNormal();

		FVector PreviousRightDirection = FVector::CrossProduct(PreviousDirection, FVector::UpVector);
		FVector PreviousLeftFirst = PreviousPoint + (-PreviousRightDirection * HalfThickness);
		FVector PreviousRightFirst = PreviousPoint + (PreviousRightDirection * HalfThickness);

		FVector NextRightDirection = FVector::CrossProduct(NextDirection, FVector::UpVector);
		FVector NextLeftFirst = ThisPoint + (-NextRightDirection * HalfThickness);
		FVector NextRightFirst = ThisPoint + (NextRightDirection * HalfThickness);

		FVector Left = LineLineIntersect(PreviousLeftFirst, PreviousDirection, NextLeftFirst, NextDirection);
		FVector Right = LineLineIntersect(PreviousRightFirst, PreviousDirection, NextRightFirst, NextDirection);

		OutVertices.Add(Left);
		OutVertices.Add(Right);
	}
}

FVector UMeshShapeFunctionLibrary::LineLineIntersect(FVector InA, FVector InVecA, FVector InB, FVector InVecB)
{
	FVector C = InB - InA;
	FVector Cross1 = FVector::CrossProduct(InVecA, InVecB);
	FVector Cross2 = FVector::CrossProduct(C, InVecB);
	return InA + (InVecA * ((FVector::DotProduct(Cross2, Cross1) / Cross1.SizeSquared())));
}