// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/ARUserWidget.h"

void UARUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
