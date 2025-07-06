// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/AuraHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/WidgetController/AuraOverlayWidgetController.h"

UAuraOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FAuraWidgetControllerParams& Params)
{
	if (nullptr == OverlayWidgetController)
	{
		OverlayWidgetController = NewObject<UAuraOverlayWidgetController>(this,OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(Params);
		OverlayWidgetController->BindValueChangeDelegates();
	}
	return OverlayWidgetController;
}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass,TEXT("Overlay Widget class is null"));
	checkf(OverlayWidgetControllerClass,TEXT("OverlayWidgetControllerClass Widget is null"));
	UUserWidget *UserWidget = CreateWidget<UUserWidget>(GetWorld(),OverlayWidgetClass);
	if (nullptr == UserWidget)
	{
		return;
	}
	OverlayWidget = Cast<UAuraUserWidget>(UserWidget);
	const FAuraWidgetControllerParams WidgetParams(PC,PS,ASC,AS);
	UAuraOverlayWidgetController *WidgetController = GetOverlayWidgetController(WidgetParams);
	if (nullptr == WidgetController)
	{
		return;
	}
	OverlayWidgetController = WidgetController;
	OverlayWidget->SetWidgetController(OverlayWidgetController);
	WidgetController->BoardcastInitValues();
	OverlayWidget->AddToViewport();
}

void AAuraHUD::BeginPlay()
{
	Super::BeginPlay();
}
