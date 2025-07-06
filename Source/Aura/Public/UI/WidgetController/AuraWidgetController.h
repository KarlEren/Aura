// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraWidgetController.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;

USTRUCT(BlueprintType)
struct FAuraWidgetControllerParams
{
	GENERATED_BODY()

	FAuraWidgetControllerParams(){}
	FAuraWidgetControllerParams(APlayerController *PC,APlayerState *PS,UAbilitySystemComponent *ASC,UAttributeSet *AS):
	PlayerController(PC),PlayerState(PS),AbilitySystemComponent(ASC),AttributeSet(AS)
	{}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerState> PlayerState = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAttributeSet> AttributeSet = nullptr;
	
	
};




UCLASS()
class AURA_API UAuraWidgetController : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void SetWidgetControllerParams(const FAuraWidgetControllerParams& Params);

	virtual void BoardcastInitValues();

	virtual void BindValueChangeDelegates();
	
protected:

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UAttributeSet> AttributeSet;
	
};
