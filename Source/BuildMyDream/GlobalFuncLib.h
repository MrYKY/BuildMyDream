#pragma once

#include <any>
#include <functional>
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

template<typename ReturnType>
inline ReturnType ExecuteWithProbability(const ReturnType& Func, const double Probability) {
	double rand = FMath::RandRange(0.0f, 1.0f);

	// 生成随机数并与概率比较
	if (rand <= Probability) {
		return  Func(); // 如果随机数小于等于概率，执行函数
	}
	return 0;
}