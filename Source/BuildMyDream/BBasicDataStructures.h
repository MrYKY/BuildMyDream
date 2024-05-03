#pragma once
#include "CoreMinimal.h"
#include "BBasicDataStructures.generated.h"

// 基本元素类型
// Basic Element Type
UENUM(BlueprintType)
enum class EBElementType : uint8
{
	Productivity,
	Manpower,
	Technology,
	End,
};

// 车辆部件类型
// Car Part Type
UENUM(BlueprintType)
enum class EBCarPartType : uint8
{
	Battery,
	Engine,
	IntelliDevice,
	End,
};

// 基本元素信息
// Basic Element Info
USTRUCT(BlueprintType)
struct FElementInfoRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mapping")
	EBElementType ElementType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mapping")
	UStaticMesh* ElementMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mapping")
	FVector MeshScale = FVector(1.0f, 1.0f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mapping")
	FRotator MeshRotation = FRotator(0.0f, 0.0f, 0.0f);
};

// 游戏阶段
// Game Stage
UENUM(BlueprintType)
enum class EBGameStage : uint8
{
	PressStage,
	PowerStage,
	ComfortStage,
	OutlookStage,
	End,
};

UENUM(BlueprintType)
enum class EBItemType : uint8
{
	Upgrader,
	Parts,
	Skill,
	End,
};

const TMap<int32,int32> Level2MoveConsumeMap = {{1,1},{2,3},{3,5},{4,9}};

USTRUCT(BlueprintType)
struct FBItemInfo : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Info")
	FName ItemID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Info")
	EBItemType ItemType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Info")
	FText ItemName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Info")
	FText ItemDescription;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Info")
	int32 ItemTechCost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Info")
	UTexture2D* ItemIcon;
	
};

USTRUCT(BlueprintType)
struct FBTask : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Task Info")
	FName TaskName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Task Info")
	int32 BatteryLevelNeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Task Info")
	int32 EngineLevelNeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Task Info")
	int32 IntelliDeviceLevelNeed;
};
