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
};


