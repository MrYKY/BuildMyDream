// Fill out your copyright notice in the Description page of Project Settings.


#include "BPlayerController.h"

#include "BElement.h"

void ABPlayerController::BeginPlay()
{
	Super::BeginPlay();
    
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}


void ABPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("LeftClick", IE_Pressed, this, &ABPlayerController::OnLeftClick);
	InputComponent->BindAction("LeftClick", IE_Released, this, &ABPlayerController::OnLeftRelease);
}


void ABPlayerController::OnLeftClick()
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Visibility, false, HitResult); // 获取鼠标光标下的命中结果
	if (HitResult.bBlockingHit)
	{
		AActor* ClickedActor = HitResult.GetActor();
		if (ClickedActor)
		{
			ABElement* Element = Cast<ABElement>(ClickedActor);
			if (Element)
			{
				Element->OnClicked();
				bIsDragging = true;
				DraggingPiece = Element;
			}
		}
	}
}

void ABPlayerController::OnLeftRelease()
{
	bIsDragging = false;
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Visibility, false, HitResult); // 获取鼠标光标下的命中结果
	if (HitResult.bBlockingHit)
	{
		AActor* ClickedActor = HitResult.GetActor();
		if (ClickedActor)
		{
			ABElement* Element = Cast<ABElement>(ClickedActor);
			if (Element)
			{
				Element->OnReleased();
			}
		}
	}
	bIsDragging = false;
}

void ABPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (bIsDragging)
	{
		FHitResult HitResult;
		GetHitResultUnderCursor(ECC_Visibility, false, HitResult); // 获取鼠标光标下的命中结果
		if (HitResult.bBlockingHit)
		{
			FVector CursorLocation, CursorDirection;
			if (DeprojectMousePositionToWorld(CursorLocation, CursorDirection))
			{
				FVector NewLocation(CursorLocation.X, 100.0f, CursorLocation.Z);
				DraggingPiece->SetActorLocation(NewLocation);
			}
		}
	}
}