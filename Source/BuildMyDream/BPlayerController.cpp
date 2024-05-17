// Fill out your copyright notice in the Description page of Project Settings.


#include "BPlayerController.h"
#include "BElement.h"

void ABPlayerController::BeginPlay()
{
	Super::BeginPlay();
	TickDelegate.BindUFunction(this, FName("FollowCursor"));
    
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
	if (!bAllowDrag)
	{
		return;
	}
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
				if(!Element->Movable)
				{
					Element->OnClicked();
					return;
				}
				Element->OnClicked();
				bIsDragging = true;
				DraggingPiece = Element;
				GetWorld()->GetTimerManager().SetTimer(TimerHandle, TickDelegate, 1.0f / 60.0f, true);
			}
		}
	}
}

void ABPlayerController::OnLeftRelease()
{
	if (!bIsDragging)
	{
		return;
	}
	bIsDragging = false;
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Visibility, false, HitResult); // 获取鼠标光标下的命中结果
	if (HitResult.bBlockingHit)
	{
		AActor* ClickedActor = HitResult.GetActor();
		if (ClickedActor)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Actor Hit"));
			ABElement* Element = Cast<ABElement>(ClickedActor);
			if (Element)
			{
				// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Hit Actor Is Element"));
				Element->OnReleased();
			}
		}
	}
}

void ABPlayerController::FollowCursor() const
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Visibility, false, HitResult); // 获取鼠标光标下的命中结果
	if (HitResult.bBlockingHit)
	{
		FVector CursorLocation, CursorDirection;
		if (DeprojectMousePositionToWorld(CursorLocation, CursorDirection))
		{
			FVector NewLocation(CursorLocation.X, 100.0f, CursorLocation.Z-10.0f);
			DraggingPiece->SetActorLocation(NewLocation);
		}
	}
}

void ABPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}