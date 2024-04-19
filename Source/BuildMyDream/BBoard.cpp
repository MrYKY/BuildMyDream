// Fill out your copyright notice in the Description page of Project Settings.


#include "BBoard.h"

#include "BElement.h"
#include "BGameModeBase.h"

// Sets default values
ABBoard::ABBoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GenerateBoard();
	EmptyCellCount = BoardSize * BoardSize;


}

// Called when the game starts or when spawned
void ABBoard::BeginPlay()
{
	Super::BeginPlay();
	GameMode = Cast<ABGameModeBase>(GetWorld()->GetAuthGameMode());
	
}

AActor* ABBoard::GenerateElementCell(int32 Row, int32 Col)
{
	--Row;
	--Col;
	if (BoardArray[Row][Col] == nullptr)
	{
		FVector Location = GetActorLocation() + FVector(Row * TileSize + TileSize/2, 0, Col * TileSize + TileSize/2);
		FRotator Rotation = FRotator(0, 0, 0);
		AActor* NewElement = GetWorld()->SpawnActor<AActor>(ElementClass, Location, Rotation);
		ABElement* Element =  Cast<ABElement>(NewElement);
		// Set Element Mesh
		Element->SetElementMesh();
		// Set Element Basic Info
		Element->Row = Row+1;
		Element->Col = Col+1;
		BindDelegates(Element);
		// Record Element in the Board
		BoardArray[Row][Col] = Element;
		--EmptyCellCount;
		return Element;
	}else
	{
		return nullptr;
	}
}

AActor* ABBoard::GenerateElement()
{
	int32 Index = FMath::RandRange(1, EmptyCellCount);
	int32 i = 1;
	for (int32 Row = 1; Row <= BoardSize; ++Row)
	{
		for (int32 Col = 1; Col <= BoardSize; ++Col)
		{
			if (BoardArray[Row-1][Col-1] == nullptr)
			{
				if (i == Index)
				{
					return GenerateElementCell(Row, Col);
				}
				++i;
			}
		}
	}
	return nullptr;
}


bool ABBoard::RemoveElement(int32 Row, int32 Col)
{
	--Row;
	--Col;
	if (BoardArray[Row][Col] != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Element Removed"));
		BoardArray[Row][Col] = nullptr;
		++EmptyCellCount;
		return true;
	}else
	{
		return false;
	}
}

void ABBoard::RemoveElementRes(int32 Row, int32 Col)
{
	RemoveElement(Row, Col);
}

bool ABBoard::PutElement(FVector Location, ABElement* Element)
{
	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Element Put Called"));
	TArray<int32> RowCol = GetRowColByLocation(Location);
	int32 Row = RowCol[0];
	int32 Col = RowCol[1];
	--Row;
	--Col;
	ABElement* PElement =  Cast<ABElement>(Element);
	if (BoardArray[Row][Col] == nullptr)
	{
		BoardArray[Row][Col] = PElement;
		--EmptyCellCount;
		PElement->Row = Row+1;
		PElement->Col = Col+1;
		PElement->SetActorLocation(GetActorLocation() + FVector(Row * TileSize + TileSize/2, 0, Col * TileSize+ TileSize/2));
		GameMode->OnMoveMadeDelegate.Broadcast();
		// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Element Put"));
		return true;
	}else{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Can't Put On This Place"));
		Row = PElement->Row-1;
		Col = PElement->Col-1;
		PElement->SetActorLocation(GetActorLocation() + FVector(Row * TileSize + TileSize/2, 0, Col * TileSize+ TileSize/2));
		return false;
	}

}

void ABBoard::PutElementRes(FVector Location, ABElement* Element)
{
	PutElement(Location, Element);
}

TArray<int32> ABBoard::GetRowColByLocation(FVector Location)
{
	TArray<int32> RowCol;
	FVector Origin = GetActorLocation();  // 获取棋盘的原点位置

	// 计算从棋盘原点到指定位置的差值
	FVector Delta = Location - Origin;
	
	int32 Col = FMath::FloorToInt(Delta.Z / TileSize);
	int32 Row = FMath::FloorToInt(Delta.X / TileSize);
	Col = FMath::Clamp(Col, 0, BoardSize - 1);
	Row = FMath::Clamp(Row, 0, BoardSize - 1);

	// 添加行和列索引到数组
	RowCol.Add(Row+1);
	RowCol.Add(Col+1);

	return RowCol;
}

void ABBoard::BindDelegates(TObjectPtr<ABElement> Element)
{
	Element->OnElementClickedDelegate.AddDynamic(this, &ABBoard::RemoveElementRes);
	Element->OnElementReleasedDelegate.AddDynamic(this, &ABBoard::PutElementRes);
}

void ABBoard::GenerateBoard()
{
	BoardArray.SetNum(BoardSize);
	for (int32 Row = 0; Row < BoardSize; ++Row)
	{
		BoardArray[Row].SetNum(BoardSize);
		for (int32 Col = 0; Col < BoardSize; ++Col)
		{
			BoardArray[Row][Col] = nullptr;
		}
	}
	
}

// Called every frame
void ABBoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

