// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/AuraHUD.h"

#include "Blueprint/UserWidget.h"

void AAuraHUD::BeginPlay()
{
	Super::BeginPlay();
	if (UUserWidget *UserWidget = CreateWidget<UUserWidget>(GetWorld(),OverlayWidgetClass))
	{
		UserWidget->AddToViewport();
	}
	
}
