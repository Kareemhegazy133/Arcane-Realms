// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/ARHUD.h"

#include "UI/Widget/ARUserWidget.h"

void AARHUD::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	Widget->AddToViewport();

}