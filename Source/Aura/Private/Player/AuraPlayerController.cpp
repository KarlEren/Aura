// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerController.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates=true;
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);//检测是否为野指针，是的话游戏崩溃
	UEnhancedInputLocalPlayerSubsystem*Subsystem=ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(AuraContext,0);//添加映射，设置此映射优先级为0
	bShowMouseCursor=true;
	DefaultMouseCursor=EMouseCursor::Default;//设置鼠标指针样式为默认值
	FInputModeGameAndUI InputModeData;//创建输入数据
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);//鼠标不会锁定到视口
	InputModeData.SetHideCursorDuringCapture(false);//设置鼠标进入屏幕时不会被隐藏
	SetInputMode(InputModeData);
}