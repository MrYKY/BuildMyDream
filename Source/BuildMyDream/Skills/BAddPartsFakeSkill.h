// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BSkillBase.h"
#include "BAddPartsFakeSkill.generated.h"

UCLASS()
class BUILDMYDREAM_API ABAddPartsFakeSkill : public ABSkillBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly,Category = "Skill")
	FBItemInfo PartInfo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* PartMesh;
	
	// Sets default values for this actor's properties
	ABAddPartsFakeSkill();

	virtual bool ApplySkill() override;

	UFUNCTION(BlueprintCallable)
	void InitPartSkill(const FBItemInfo& PartInformation);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
