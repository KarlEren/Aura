// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/AuraEffectActor.h"

#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Components/SphereComponent.h"


AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("Root"));
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void AAuraEffectActor::ApplyEffect(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	checkf(GameplayEffectClass,TEXT("buff no set"))
	if (IAbilitySystemInterface *IAC = Cast<IAbilitySystemInterface>(TargetActor))
	{
		if (UAbilitySystemComponent *AbilitySystem = IAC->GetAbilitySystemComponent())
		{
			FGameplayEffectContextHandle GameplayEffectContext =AbilitySystem->MakeEffectContext();
			GameplayEffectContext.AddSourceObject(this);
			FGameplayEffectSpecHandle GameplayEffectSpec = AbilitySystem->MakeOutgoingSpec(GameplayEffectClass,1.f,GameplayEffectContext);
			AbilitySystem->ApplyGameplayEffectSpecToSelf(*GameplayEffectSpec.Data.Get());
			Destroy();
		}
	}
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	checkf(GameplayEffectClass,TEXT("buff no set"))
	IAbilitySystemInterface *IAC = Cast<IAbilitySystemInterface>(TargetActor);
	if (!IAC)
	{
		return;
	}
	UAbilitySystemComponent *AbilitySystem = IAC->GetAbilitySystemComponent();
	if (!AbilitySystem)
	{
		return;
	}
	FGameplayEffectContextHandle GameplayEffectContext =AbilitySystem->MakeEffectContext();
	GameplayEffectContext.AddSourceObject(this);
	const FGameplayEffectSpecHandle GameplayEffectSpec = AbilitySystem->MakeOutgoingSpec(GameplayEffectClass,1.f,GameplayEffectContext);
	const FActiveGameplayEffectHandle ActiveGameplayEffectHandle=AbilitySystem->ApplyGameplayEffectSpecToSelf(*GameplayEffectSpec.Data.Get());
	if (!GameplayEffectSpec.Data)
	{
		return;
	}
	if (!GameplayEffectSpec.Data->Def)
	{
		return;
	}
	const bool bIsInfinite = GameplayEffectSpec.Data->Def->DurationPolicy==EGameplayEffectDurationType::Infinite;
	if (bIsInfinite && InfiniteRemovePolicy == EAuraRemoveEffectPolicy::RemoveOnEndOverlap)
	{
		ActiveEffectHandles.Add(ActiveGameplayEffectHandle,AbilitySystem);
	}
}

void AAuraEffectActor::OnOverlap(AActor* TargetActor)
{
	if (InstantPolicy == EAuraApplyEffectPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor,InstantGameplayEffectClass);
	}
	if (DurationPolicy == EAuraApplyEffectPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor,DurationGameplayEffectClass);
	}
	if (InfinitePolicy == EAuraApplyEffectPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor,InfiniteGameplayEffectClass);
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (InstantPolicy == EAuraApplyEffectPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor,InstantGameplayEffectClass);
	}
	if (DurationPolicy == EAuraApplyEffectPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor,DurationGameplayEffectClass);
	}
	if (InfinitePolicy == EAuraApplyEffectPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor,InfiniteGameplayEffectClass);
	}
	if (InfiniteRemovePolicy ==  EAuraRemoveEffectPolicy::RemoveOnEndOverlap)
	{
		IAbilitySystemInterface *IAC = Cast<IAbilitySystemInterface>(TargetActor);
		if (!IAC)
		{
			return;
		}
		UAbilitySystemComponent *AbilitySystem = IAC->GetAbilitySystemComponent();
		if (!AbilitySystem)
		{
			return;
		}
		TArray<FActiveGameplayEffectHandle> EffectToRemove;
		for (auto& HandlePair : ActiveEffectHandles)
		{
			if (AbilitySystem == HandlePair.Value)
			{
				AbilitySystem->RemoveActiveGameplayEffect(HandlePair.Key,1);
				EffectToRemove.Add(HandlePair.Key);
			}
		}
		for (auto& Effect : EffectToRemove)
		{
			ActiveEffectHandles.FindAndRemoveChecked(Effect);
		}
	}
}


