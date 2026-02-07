// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/AuraOverlayWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
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
			TWeakObjectPtr WeakThis = this;
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()).AddLambda(
				[WeakThis](const FOnAttributeChangeData& Data)
				{
					if (auto ThisController = Cast<UAuraOverlayWidgetController>(WeakThis))
					{
						ThisController->OnHealthChanged.Broadcast(Data.NewValue);
					}
				}
			);
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute()).AddLambda(
			[WeakThis](const FOnAttributeChangeData& Data)
				{
					if (auto ThisController = Cast<UAuraOverlayWidgetController>(WeakThis))
					{
						ThisController->OnMaxHealthChanged.Broadcast(Data.NewValue);
					}
				}
			);
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute()).AddLambda(
			[WeakThis](const FOnAttributeChangeData& Data)
				{
					if (auto ThisController = Cast<UAuraOverlayWidgetController>(WeakThis))
					{
						ThisController->OnManaChanged.Broadcast(Data.NewValue);
					}
				}
			);
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute()).AddLambda(
			[WeakThis](const FOnAttributeChangeData& Data)
				{	
					if (auto ThisController = Cast<UAuraOverlayWidgetController>(WeakThis))
					{
						ThisController->OnMaxManaChanged.Broadcast(Data.NewValue);
					}
				}
			);
			Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->OnAuraEffectTagDelegate.AddLambda(
				[WeakThis](const FGameplayTagContainer& GameplayTagContainer)
				{
					if (auto ThisController = Cast<UAuraOverlayWidgetController>(WeakThis))
					{
						for (const FGameplayTag& GameplayTag : GameplayTagContainer)
						{
							FGameplayTag MatchTag = FGameplayTag::RequestGameplayTag(FName("Message"));
							if (GameplayTag.MatchesTag(MatchTag))
							{
								FAuraWidgetRow *Row = ThisController->GetTableRowByTag<FAuraWidgetRow>(ThisController->WidgetDataTable,GameplayTag);
								if (Row)
								{
									ThisController->OnMessageTag.Broadcast(*Row);
								}
							}
						}
					}	
				}
			);
		}
	}
}


