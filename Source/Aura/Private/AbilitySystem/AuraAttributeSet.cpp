// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"

UAuraAttributeSet::UAuraAttributeSet()
{
	InitHealth(50.f);
	InitMaxHealth(100.f);
	InitMana(50.f);
	InitMaxMana(100.f);
}

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Health,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,MaxHealth,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Mana,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,MaxMana,COND_None,REPNOTIFY_Always);
}

void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Health,OldHealth)
}

void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,MaxHealth,OldMaxHealth)
}

void UAuraAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Mana,OldMana)
}

void UAuraAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,MaxMana,OldMaxMana)
}

void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
}

void UAuraAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	FAuraEffectProps AuraEffectProps;
	UpdateAuraEffectProps(Data, AuraEffectProps);
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(),0,GetMaxHealth()));
	}
	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(),0,GetMaxMana()));
	}
}

void UAuraAttributeSet::UpdateAuraEffectProps(const struct FGameplayEffectModCallbackData& Data,
	FAuraEffectProps& OutEffectProps)const
{
	OutEffectProps.EffectContextHandle = Data.EffectSpec.GetEffectContext();
	OutEffectProps.SourceASC = OutEffectProps.EffectContextHandle.GetInstigatorAbilitySystemComponent();
	if (!OutEffectProps.SourceASC)
	{
		return;
	}
	if (!OutEffectProps.SourceASC->AbilityActorInfo)
	{
		return;
	}
	if (!OutEffectProps.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		return;
	}
	OutEffectProps.SourceAvatarActor = OutEffectProps.SourceASC->AbilityActorInfo->AvatarActor.Get();
	OutEffectProps.SourceController = OutEffectProps.SourceASC->AbilityActorInfo->PlayerController.Get();
	if (!OutEffectProps.SourceController && OutEffectProps.SourceAvatarActor)
	{
		if (APawn *SourcePawn = Cast<APawn>(OutEffectProps.SourceAvatarActor))
		{
			OutEffectProps.SourceController = SourcePawn->GetController();
		}
	}
	if (OutEffectProps.SourceController)
	{
		OutEffectProps.SourceCharacter =  OutEffectProps.SourceController->GetCharacter();
	}

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		OutEffectProps.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		OutEffectProps.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		OutEffectProps.TargetCharacter = Cast<ACharacter>(OutEffectProps.TargetAvatarActor);
		IAbilitySystemInterface *IAC = Cast<IAbilitySystemInterface>(OutEffectProps.TargetAvatarActor);
		if (!IAC)
		{
			return;
		}
		UAbilitySystemComponent *AbilitySystem = IAC->GetAbilitySystemComponent();
		if (!AbilitySystem)
		{
			return;
		}
		OutEffectProps.TargetASC = AbilitySystem;
	}
}



