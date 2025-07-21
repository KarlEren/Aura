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

void AAuraEffectActor::OnOverlap(AActor* TargetActor)
{
	if (InstantPolicy == EAuraApplyEffectPolicy::ApplyOnOverlap)
	{
		ApplyEffect(TargetActor,InstantGameplayEffectClass);
	}
	if (DurationPolicy == EAuraApplyEffectPolicy::ApplyOnOverlap)
	{
		ApplyEffect(TargetActor,DurationGameplayEffectClass);
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (InstantPolicy == EAuraApplyEffectPolicy::ApplyOnEndOverlap)
	{
		ApplyEffect(TargetActor,InstantGameplayEffectClass);
	}
	if (DurationPolicy == EAuraApplyEffectPolicy::ApplyOnEndOverlap)
	{
		ApplyEffect(TargetActor,InstantGameplayEffectClass);
	}
}


