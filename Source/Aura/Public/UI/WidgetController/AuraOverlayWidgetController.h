// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "AuraOverlayWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnValueChanged,float,NewValue);


/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class AURA_API UAuraOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
public:
	virtual void BoardcastInitValues() override;

	virtual void BindValueChangeDelegates() override;

	UPROPERTY(BlueprintAssignable,BlueprintCallable)
	FOnValueChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable,BlueprintCallable)
	FOnValueChanged OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable,BlueprintCallable)
	FOnValueChanged OnManaChanged;

	UPROPERTY(BlueprintAssignable,BlueprintCallable)
	FOnValueChanged OnMaxManaChanged;
private:

	void HandleHealthChanged(const FOnAttributeChangeData& Data)const;
	void HandleMaxHealthChanged(const FOnAttributeChangeData& Data)const;
	void HandleManaChanged(const FOnAttributeChangeData& Data)const;
	void HandleMaxManaChanged(const FOnAttributeChangeData& Data)const;
	
};
