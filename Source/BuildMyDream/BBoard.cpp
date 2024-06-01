// Fill out your copyright notice in the Description page of Project Settings.


#include "BBoard.h"

#include "BElement.h"
#include "BGameModeBase.h"
#include "Tasks/Task.h"

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
	GameMode->OnMoveMadeDelegate.AddDynamic(this, &ABBoard::UpdateAllElementScore);
	GameMode->OnMoveMadeDelegate.AddDynamic(this, &ABBoard::UpdateAllElementLockRound);
	
	
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
		// Set Element Basic Info
		Element->Row = Row+1;
		Element->Col = Col+1;
		BindDelegates(Element);
		// Record Element in the Board
		BoardArray[Row][Col] = Element;
		--EmptyCellCount;
		// TryMerge(Element,true); // 后续确定类型后再进行消除尝试。
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
					AActor* NewElement =  GenerateElementCell(Row, Col);
					ABElement* Element = Cast<ABElement>(NewElement);
					Element->SetElementMesh();
					TryMerge(Element,true);
					return Element;
				}
				++i;
			}
		}
	}
	return nullptr;
}

AActor* ABBoard::GenerateElementType(EBElementType Type)
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
					AActor* NewElement =  GenerateElementCell(Row, Col);
					ABElement* Element = Cast<ABElement>(NewElement);
					Element->SetElementType(Type);
					Element->SetElementMesh();
					if (Type == EBElementType::Malfunction)
					{
						Element->LockElement(100000);
					}
					TryMerge(Element,true);
					return Element;
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
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, TEXT("Element Removed"));
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

	if((abs(PElement->Row-1-Row)<=PElement->MoveRange && PElement->Col-1==Col)
		|| (abs(PElement->Col-1-Col)<=PElement->MoveRange && PElement->Row-1==Row))
	{
		if(BoardArray[Row][Col] == nullptr)
		{
			BoardArray[Row][Col] = PElement;
			--EmptyCellCount;
			if(Row+1 != PElement->Row || Col+1 != PElement->Col)
			{
				PElement->Row = Row+1;
				PElement->Col = Col+1;
				GameMode->OnMoveMadeDelegate.Broadcast(PElement);
			}
			SetElementLocation(PElement);
			TryMerge(PElement, true);
			return true;
		}else if(BoardArray[Row][Col]->Movable)
		{
			TObjectPtr<ABElement> SwitchedElement = BoardArray[Row][Col];
			BoardArray[Row][Col] = PElement;
			BoardArray[PElement->Row-1][PElement->Col-1] = SwitchedElement;
			if(Row+1 != PElement->Row || Col+1 != PElement->Col)
			{
				SwitchedElement->Row = PElement->Row;
				SwitchedElement->Col = PElement->Col;
				PElement->Row = Row+1;
				PElement->Col = Col+1;
				GameMode->OnMoveMadeDelegate.Broadcast(PElement);
			}
			SetElementLocation(PElement);
			SetElementLocation(SwitchedElement);
			TryMerge(PElement, true);
			TryMerge(SwitchedElement, true);
			return true;
		}else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("SwitchedElement Can't Be Moved"));
			BoardArray[PElement->Row-1][PElement->Col-1] = PElement;
			SetElementLocation(PElement);
			return false;
		}
	}else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Can't Put On This Place"));
		BoardArray[PElement->Row-1][PElement->Col-1] = PElement;
		SetElementLocation(PElement);
		return false;
	}
}

void ABBoard::PutElementRes(FVector Location, ABElement* Element)
{
	PutElement(Location, Element);
}

void ABBoard::LockRandomElement()
{
	int32 OccupiedCellCount = BoardSize * BoardSize - EmptyCellCount;
	int32 rand = FMath::RandRange(1, OccupiedCellCount);
	int32 i = 1;
	for (int32 Row = 1; Row <= BoardSize; ++Row)
	{
		for (int32 Col = 1; Col <= BoardSize; ++Col)
		{
			if (BoardArray[Row-1][Col-1] != nullptr )
			{
				if (i == rand && BoardArray[Row-1][Col-1]->ElementType!=EBElementType::Malfunction)
				{
					BoardArray[Row-1][Col-1]->LockElement(5);
					return;
				}else
				{
					++i;
				}
			}
		}
	}
}

void ABBoard::UpdateAllElementScore(ABElement* MovedElement)
{
	for (int32 Row = 1; Row <= BoardSize; ++Row)
	{
		for (int32 Col = 1; Col <= BoardSize; ++Col)
		{
			if (BoardArray[Row-1][Col-1] != nullptr )
			{
				if(BoardArray[Row-1][Col-1]->CurrentScore > BoardArray[Row-1][Col-1]->Level)
				{
					BoardArray[Row-1][Col-1]->CurrentScore--;
					BoardArray[Row-1][Col-1]->OnCurrentScoreChangedDelegate.Broadcast();
				}
			}
		}
	}
}

void ABBoard::UpdateAllElementLockRound(ABElement* MovedElement)
{
	for (int32 Row = 1; Row <= BoardSize; ++Row)
	{
		for (int32 Col = 1; Col <= BoardSize; ++Col)
		{
			if (BoardArray[Row-1][Col-1] != nullptr )
			{
				if(BoardArray[Row-1][Col-1]->LockedRound > 0)
				{
					BoardArray[Row-1][Col-1]->LockedRound--;
					BoardArray[Row-1][Col-1]->OnLockedRoundChangedDelegate.Broadcast();
				}
				if(BoardArray[Row-1][Col-1]->LockedRound==0)
				{
					BoardArray[Row-1][Col-1]->UnlockElement();
					TryMerge(BoardArray[Row-1][Col-1],true);
				}
			}
		}
	}
}

TArray<int32> ABBoard::GetRowColByLocation(FVector Location) const
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

bool ABBoard::TryMerge(TObjectPtr<ABElement> Element, bool bFirstCall)
{
	static TArray<TObjectPtr<ABElement>> MergeArray;
	EBElementType ElementType = Element->ElementType;
	int32 Row = Element->Row;
	int32 Col = Element->Col;
	MergeArray.Add(Element);
	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Element Added To Merge Array"));
	static std::vector<std::vector<bool>> Visited(BoardSize, std::vector<bool>(BoardSize, false));
	Visited[Row-1][Col-1] = true;
	constexpr int32 DCol[4] = {0, 0, -1, 1};
	constexpr int32 DRow[4] = {-1, 1, 0, 0};

	for(int32 i = 0; i < 4; ++i)
	{
		int32 NewRow = Row + DRow[i]-1;
		int32 NewCol = Col + DCol[i]-1;
		if (NewRow >= 0 && NewRow < BoardSize && NewCol >= 0 && NewCol < BoardSize)
		{
			if (BoardArray[NewRow][NewCol] && !Visited[NewRow][NewCol])
			{
				if (BoardArray[NewRow][NewCol]->ElementType == ElementType && BoardArray[NewRow][NewCol]->Movable
					&& BoardArray[NewRow][NewCol]->ElementType!=EBElementType::End)
				{
					Visited[NewRow][NewCol] = true;
					TryMerge(BoardArray[NewRow][NewCol], false);
					// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Called Self"));
				}
			}
		}
	}
	if(bFirstCall)
	{
		if(MergeArray.Num()>=3)
		{
			// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("3 In Neighbourhood"));
			for(int32 i = 0; i<MergeArray.Num(); ++i)
			{
				RemoveElement(MergeArray[i]->Row, MergeArray[i]->Col);
				if(i == 0)
				{
					AActor* NewElement =  GenerateElementCell(MergeArray[0]->Row, MergeArray[0]->Col);
					ABElement* ElementStay = Cast<ABElement>(NewElement);
					ElementStay->SetElementType(MergeArray[0]->ElementType);
					ElementStay->SetElementMesh();
				}
				GameMode->OnMergeMadeDelegate.Broadcast(MergeArray[i]);
				MergeArray[i]->Destroy();
			}
			MergeArray.Empty();
			Visited = std::vector<std::vector<bool>>(BoardSize, std::vector<bool>(BoardSize, false));
			return true;
		}else{
			MergeArray.Empty();
			Visited = std::vector<std::vector<bool>>(BoardSize, std::vector<bool>(BoardSize, false));
			// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Info Reseted"));
			return false;
		}
	}

	return true;
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

void ABBoard::SetElementLocation(TObjectPtr<ABElement> Element)
{
	Element->SetActorLocation(GetActorLocation() + FVector((Element->Row-1) * TileSize + TileSize/2, 0, (Element->Col-1) * TileSize+ TileSize/2));
}

