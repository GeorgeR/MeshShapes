#include "MeshShapeFunctionLibrary.h"
#include "GeomTools.h"

void UMeshShapeFunctionLibrary::CreateCircle(float InRadius, int32 InSegments, FMeshData& OutData)
{
	CreateCircleVertices(InRadius, InSegments, OutData.Vertices);
	OutData.Fill(OutData.Vertices.Num());

	Triangulate(OutData, ETriangulationMethod::Fan);
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

void UMeshShapeFunctionLibrary::CreateRectangle(float InWidth, float InHeight, FMeshData& OutData)
{
	CreateRectangleVertices(InWidth, InHeight, OutData.Vertices);
	OutData.Fill(OutData.Vertices.Num());

	Triangulate(OutData, ETriangulationMethod::EarClipping);
}

void UMeshShapeFunctionLibrary::CreateRectangleVertices(float InWidth, float InHeight, TArray<FVector>& OutVertices)
{
	OutVertices.Empty();

	float HalfWidth = InWidth * 0.5f;
	float HalfHeight = InHeight * 0.5f;

	OutVertices.Add(FVector(-HalfWidth, +HalfHeight, 0.0f));
	OutVertices.Add(FVector(+HalfWidth, +HalfHeight, 0.0f));
	OutVertices.Add(FVector(-HalfWidth, -HalfHeight, 0.0f));
	OutVertices.Add(FVector(+HalfWidth, -HalfHeight, 0.0f));
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

		OutData.Vertices.Add(Left);
		OutData.Vertices.Add(Right);
	}
}

void UMeshShapeFunctionLibrary::Triangulate(FMeshData& InOutData, ETriangulationMethod InMethod, bool bFlip /*= false*/)
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
				InOutData.Indices.Add(0);
				InOutData.Indices.Add(i + 1);
				InOutData.Indices.Add(i);
			}

			InOutData.Indices.Add(0);
			InOutData.Indices.Add(1);
			InOutData.Indices.Add(InOutData.Vertices.Num() - 1);
		}
		else if (InMethod == ETriangulationMethod::Grid)
		{

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
						InOutData.Indices.Add(ClipVertices.IndexOfByKey(Vertex));
					}
				}
			}
		}
	}

	if (bFlip)
		Algo::Reverse(InOutData.Indices);
}

FVector UMeshShapeFunctionLibrary::LineLineIntersect(FVector InA, FVector InVecA, FVector InB, FVector InVecB)
{
	FVector C = InB - InA;
	FVector Cross1 = FVector::CrossProduct(InVecA, InVecB);
	FVector Cross2 = FVector::CrossProduct(C, InVecB);
	return InA + (InVecA * ((FVector::DotProduct(Cross2, Cross1) / Cross1.SizeSquared())));
}