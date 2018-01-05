#include "MeshShapeFunctionLibrary.h"
#include "GeomTools.h"

void UMeshShapeFunctionLibrary::CreateCircle(float InRadius, int32 InSegments, FMeshData& OutData)
{
	CreateCircleVertices(InRadius, InSegments, OutData.Vertices);
	OutData.Fill(OutData.Vertices.Num());

	Triangulate(OutData, ETriangulationMethod::Fan, true);
}

void UMeshShapeFunctionLibrary::CreateCircleVertices(float InRadius, int32 InSegments, TArray<FVector>& OutVertices)
{
	OutVertices.Empty();

	float Step = (PI * 2.0f) / InSegments;
	OutVertices.Add(FVector::ZeroVector);
	for (auto i = 0; i < InSegments; i++)
	{
		FVector Vertex;
		Vertex.X = InRadius * FMath::Cos(i * Step);
		Vertex.Y = InRadius * FMath::Sin(i * Step);
		Vertex.Z = 0.0f;
		OutVertices.Add(Vertex);
	}
}

void UMeshShapeFunctionLibrary::UpdateCircle(float InRadius, FMeshData& InOutData)
{
	int32 Segments = InOutData.Vertices.Num() - 1;

	CreateCircleVertices(InRadius, Segments, InOutData.Vertices);
}

void UMeshShapeFunctionLibrary::CreateArc(float InRadius, int32 InSegments, float InStartAngle, float InEndAngle, bool bWedge, FMeshData& OutData)
{
	if (bWedge)
		OutData.Vertices.Add(FVector::ZeroVector);

	CreateArcVertices(InRadius, InSegments, InStartAngle, InEndAngle, OutData.Vertices);
	OutData.Fill(OutData.Vertices.Num());

	Triangulate(OutData, ETriangulationMethod::Fan, true);
}

void UMeshShapeFunctionLibrary::CreateArcVertices(float InRadius, int32 InSegments, float InStartAngle, float InEndAngle, TArray<FVector>& OutVertices)
{
	float Step = (PI * 2.0f) / InSegments;
	// TODO
}

void UMeshShapeFunctionLibrary::CreateRectangle(float InWidth, float InHeight, FMeshData& OutData)
{
	CreateRectangleVertices(InWidth, InHeight, OutData.Vertices);
	OutData.Fill(OutData.Vertices.Num());

	Triangulate(OutData, ETriangulationMethod::Grid);
}

void UMeshShapeFunctionLibrary::CreateRectangleVertices(float InWidth, float InHeight, TArray<FVector>& OutVertices)
{
	OutVertices.Empty();

	float HalfWidth = InWidth * 0.5f;
	float HalfHeight = InHeight * 0.5f;

	OutVertices.Add(FVector(-HalfWidth, -HalfHeight, 0.0f));
	OutVertices.Add(FVector(+HalfWidth, -HalfHeight, 0.0f));
	OutVertices.Add(FVector(-HalfWidth, +HalfHeight, 0.0f));
	OutVertices.Add(FVector(+HalfWidth, +HalfHeight, 0.0f));
}

void UMeshShapeFunctionLibrary::UpdateRectangle(float InWidth, float InHeight, FMeshData& InOutData)
{
	CreateRectangleVertices(InWidth, InHeight, InOutData.Vertices);
}

void UMeshShapeFunctionLibrary::CreatePolygon(TArray<FVector> InVertices, FMeshData& OutData)
{
	OutData.Vertices = InVertices;
	OutData.Fill(OutData.Vertices.Num());

	Triangulate(OutData, ETriangulationMethod::EarClipping);
}

void UMeshShapeFunctionLibrary::StrokePath(TArray<FVector>& InPoints, float& InThickness, bool bClosed /*= true*/, FMeshData& OutData)
{
	float HalfThickness = InThickness * 0.5f;

	FVector Min = InPoints[0];
	FVector Max = InPoints[0];

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

		FVector Left(0);
		FVector Right(0);
		if (!bClosed && (i == 0 || i == InPoints.Num() - 1))
		{
			// NOTE: I don't know why I have to do this
			if (i == InPoints.Num() - 1)
			{
				Left = NextRightFirst;
				Right = NextLeftFirst;
			}
			else 
			{
				Left = NextLeftFirst;
				Right = NextRightFirst;
			}
		}
		else
		{
			Left = LineLineIntersect(PreviousLeftFirst, PreviousDirection, NextLeftFirst, NextDirection);
			Right = LineLineIntersect(PreviousRightFirst, PreviousDirection, NextRightFirst, NextDirection);
		}
		
		Min = Min.ComponentMin(Left);
		Min = Min.ComponentMin(Right);
		
		Max = Max.ComponentMax(Left);
		Max = Max.ComponentMax(Right);

		OutData.Vertices.Add(Left);
		OutData.Vertices.Add(Right);
	}

	FVector OneOverExtents = FVector(1.0f) / (Max - Min);

	TFunction<FColor(FVector&)> NormalizePosition = [&](FVector& Position) -> FColor {
		FVector Result = (Position - Min) * OneOverExtents;
		return FColor(
			(uint8)FMath::FloorToInt(Result.X * 255), 
			(uint8)FMath::FloorToInt(Result.Y * 255), 
			(uint8)FMath::FloorToInt(Result.Z * 255));
	};

	for (auto i = 0; i < InPoints.Num(); i++)
	{
		FColor NormalizedPosition = NormalizePosition(InPoints[i]);
		OutData.Colors.Add(NormalizedPosition); // Encode center in vertex color
		OutData.Colors.Add(NormalizedPosition);
	}

	Triangulate(OutData, ETriangulationMethod::Grid, bClosed);

	OutData.Fill(OutData.Vertices.Num());
}

void UMeshShapeFunctionLibrary::Triangulate(FMeshData& InOutData, ETriangulationMethod InMethod, bool bClosed, bool bFlip /*= false*/)
{
	InOutData.Indices.Empty();

	if (InOutData.Vertices.Num() == 3)
	{
		InOutData.Indices = { 0, 1, 2 };
	}
	else
	{
		if (InMethod == ETriangulationMethod::Fan)
		{
			for (auto i = 1; i < InOutData.Vertices.Num(); i++)
			{
				InOutData.Indices.Add(0);
				InOutData.Indices.Add(i + 1);
				InOutData.Indices.Add(i);
			}

			if (bClosed)
			{
				InOutData.Indices.Add(0);
				InOutData.Indices.Add(1);
				InOutData.Indices.Add(InOutData.Vertices.Num() - 1);
			}
		}
		else if (InMethod == ETriangulationMethod::Grid)
		{
			for (auto i = 0; i < InOutData.Vertices.Num() - 2; i += 2)
			{
				InOutData.Indices.Add(i + 0);
				InOutData.Indices.Add(i + 2);
				InOutData.Indices.Add(i + 1);
				InOutData.Indices.Add(i + 1);
				InOutData.Indices.Add(i + 2);
				InOutData.Indices.Add(i + 3);
			}

			if (bClosed)
			{
				int32 SecondLastVertexIndex = InOutData.Vertices.Num() - 2;
				InOutData.Indices.Add(SecondLastVertexIndex);
				InOutData.Indices.Add(0);
				InOutData.Indices.Add(SecondLastVertexIndex + 1);
				InOutData.Indices.Add(SecondLastVertexIndex + 1);
				InOutData.Indices.Add(0);
				InOutData.Indices.Add(1);
			}
		}
		else if (InMethod == ETriangulationMethod::EarClipping)
		{
			float ZHeight = InOutData.Vertices[0].Z;
			TArray<FClipSMVertex> ClipVertices;
			for (auto i = 0; i < InOutData.Vertices.Num(); i++)
			{
				FClipSMVertex Vertex;
				Vertex.Pos = InOutData.Vertices[i];
				ClipVertices.Add(Vertex);
			}

			FClipSMPolygon Polygon(0);
			Polygon.Vertices = ClipVertices;

			TArray<FClipSMTriangle> ClipTriangles;
			if (FGeomTools::TriangulatePoly(ClipTriangles, Polygon, true))
			{
				for (auto i = 0; i < ClipTriangles.Num(); i++)
				{
					FClipSMTriangle Triangle = ClipTriangles[i];
					for (auto j = 0; j < 3; j++)
					{
						FClipSMVertex Vertex = Triangle.Vertices[j];
						for(auto k = 0; k < ClipVertices.Num(); k++)
							if (ClipVertices[k].Pos == Vertex.Pos)
							{
								InOutData.Indices.Add(k);
								break;
							}
					}
				}
			}
		}
	}

	if (bFlip)
		Algo::Reverse(InOutData.Indices);
}

void UMeshShapeFunctionLibrary::CreateUVFit(TArray<FVector>& InVertices, TArray<FVector2D>& OutUVs)
{
	FBox2D Bounds;
	GetBounds(InVertices, Bounds);

	FVector2D OneOverBoundsSize = Bounds.GetSize();
	OneOverBoundsSize = FVector2D(1.0f / OneOverBoundsSize.X, 1.0f / OneOverBoundsSize.Y);

	for (auto i = 0; i < InVertices.Num(); i++)
	{
		FVector2D Vertex2D = FVector2D(InVertices[i].Y - Bounds.Min.X, -InVertices[i].X - Bounds.Min.Y);
		Vertex2D *= OneOverBoundsSize;
		OutUVs.Add(Vertex2D);
	}
}

void UMeshShapeFunctionLibrary::GetBounds(TArray<FVector>& InVertices, FBox2D& OutBounds)
{
	FVector2D Min(FLT_MAX, FLT_MAX);
	FVector2D Max(FLT_MIN, FLT_MIN);
	for (auto i = 0; i < InVertices.Num(); i++)
	{
		FVector Vertex = InVertices[i];
		Min = FVector2D(FMath::Min(Min.X, Vertex.X), FMath::Min(Min.Y, Vertex.Y));
		Max = FVector2D(FMath::Max(Max.X, Vertex.X), FMath::Max(Max.Y, Vertex.Y));
	}

	OutBounds = FBox2D(Min, Max);
}

FVector UMeshShapeFunctionLibrary::LineLineIntersect(FVector InA, FVector InVecA, FVector InB, FVector InVecB)
{
	FVector C = InB - InA;
	FVector Cross1 = FVector::CrossProduct(InVecA, InVecB);
	FVector Cross2 = FVector::CrossProduct(C, InVecB);
	return InA + (InVecA * ((FVector::DotProduct(Cross2, Cross1) / Cross1.SizeSquared())));
}