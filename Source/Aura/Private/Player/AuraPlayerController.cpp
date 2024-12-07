// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerController.h"
#include "EnhancedInputComponent.h"

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

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputComponent*EnhancedInputComponent=CastChecked<UEnhancedInputComponent>(InputComponent);//如果类型转换失败，出发断言
	EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AAuraPlayerController::Move);//绑定回调函数
	
	
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisValue=InputActionValue.Get<FVector2D>();
	//计算前向量和右向量
	const FRotator Rotation=GetControlRotation();
	const FRotator YawRotation(0.0f,Rotation.Yaw,0.0f);
	const FVector FowardDirection=FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection=FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn*ControlledPawn=GetPawn<APawn>())
	{
		//添加移动输入
		ControlledPawn->AddMovementInput(FowardDirection,InputAxisValue.Y);
		ControlledPawn->AddMovementInput(RightDirection,InputAxisValue.X);
	}
}
