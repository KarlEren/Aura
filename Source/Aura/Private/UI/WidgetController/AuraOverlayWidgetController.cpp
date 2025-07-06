// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/AuraOverlayWidgetController.h"

#include "AbilitySystem/AuraAttributeSet.h"

void UAuraOverlayWidgetController::BoardcastInitValues()
{
	Super::BoardcastInitValues();
	if (UAuraAttributeSet *AuraAttributeSet = Cast<UAuraAttributeSet>(AttributeSet))
	{
		OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
		OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());
		OnManaChanged.Broadcast(AuraAttributeSet->GetMana());
		OnMaxManaChanged.Broadcast(AuraAttributeSet->GetMaxMana());
	}
}

void UAuraOverlayWidgetController::BindValueChangeDelegates()
{
	Super::BindValueChangeDelegates();
	if (UAuraAttributeSet *AuraAttributeSet = Cast<UAuraAttributeSet>(AttributeSet))
	{
		if (AbilitySystemComponent)
		{
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()).
			AddUObject(this,&UAuraOverlayWidgetController::HandleHealthChanged);
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute()).
			AddUObject(this,&UAuraOverlayWidgetController::HandleMaxHealthChanged);
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute()).
			AddUObject(this,&UAuraOverlayWidgetController::HandleManaChanged);
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute()).
			AddUObject(this,&UAuraOverlayWidgetController::HandleMaxManaChanged);
		}
	}
}

void UAuraOverlayWidgetController::HandleHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UAuraOverlayWidgetController::HandleMaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UAuraOverlayWidgetController::HandleManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UAuraOverlayWidgetController::HandleMaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}
