// Fill out your copyright notice in the Description page of Project Settings.


#include "BBoard.h"

// Sets default values
ABBoard::ABBoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GenerateBoard();

}

// Called when the game starts or when spawned
void ABBoard::BeginPlay()
{
	Super::BeginPlay();
	
}

bool ABBoard::GenerateElement(int32 Row, int32 Col)
{
	--Row;
	--Col;
	if (BoardArray[Row][Col] == nullptr)
	{
		FVector Location = GetActorLocation() + FVector(Row * TileSize, 0, Col * TileSize);
		FRotator Rotation = FRotator(0, 0, 0);
		AActor* NewElement = GetWorld()->SpawnActor<AActor>(ElementClass, Location, Rotation);
		BoardArray[Row][Col] = NewElement;
		return true;
	}else
	{
		return false;
	}
}

bool ABBoard::RemoveElement(int32 Row, int32 Col)
{
	--Row;
	--Col;
	if (BoardArray[Row][Col] != nullptr)
	{
		BoardArray[Row][Col] = nullptr;
		return true;
	}else
	{
		return false;
	}
}

bool ABBoard::PutElement(FVector Location, AActor* Element)
{
	TArray<int32> RowCol = GetRowColByLocation(Location);
	int32 Row = RowCol[0];
	int32 Col = RowCol[1];
	--Row;
	--Col;
	if (BoardArray[Row][Col] == nullptr)
	{
		BoardArray[Row][Col] = Element;
		Element->SetActorLocation(GetActorLocation() + FVector(Row * TileSize, 0, Col * TileSize));
		return true;
	}else{
		return false;
	}

}

TArray<int32> ABBoard::GetRowColByLocation(FVector Location)
{
	TArray<int32> RowCol;
	FVector Origin = GetActorLocation();  // 获取棋盘的原点位置

	// 计算从棋盘原点到指定位置的差值
	FVector Delta = Location - Origin;
	
	int32 Col = FMath::FloorToInt(Delta.X / TileSize);
	int32 Row = FMath::FloorToInt(Delta.Z / TileSize);

	// 添加行和列索引到数组
	RowCol.Add(Row+1);
	RowCol.Add(Col+1);

	return RowCol;
}

void ABBoard::GenerateBoard()
{
	BoardArray.SetNum(BoardSize);
	for (int32 Row = 0; Row < BoardSize; ++Row)
	{
		BoardArray[Row].SetNum(BoardSize);
	}
}

// Called every frame
void ABBoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

