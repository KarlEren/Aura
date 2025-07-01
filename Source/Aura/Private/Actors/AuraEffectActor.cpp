// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/AuraEffectActor.h"

#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Components/SphereComponent.h"


AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SetRootComponent(StaticMeshComponent);
	SphereComponent->SetupAttachment(StaticMeshComponent);
}

void AAuraEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if (IAbilitySystemInterface *IAC = Cast<IAbilitySystemInterface>(OtherActor))
	{
		if (UAuraAbilitySystemComponent *AuraAbilityComp = Cast<UAuraAbilitySystemComponent>(IAC->GetAbilitySystemComponent()))
		{
			if (const UAuraAttributeSet *AuraAttributeSet = Cast<UAuraAttributeSet>(AuraAbilityComp->GetAttributeSet(UAuraAttributeSet::StaticClass())))
			{
				UAuraAttributeSet *NonConstAuraAttributeSet = const_cast<UAuraAttributeSet *>(AuraAttributeSet);
				NonConstAuraAttributeSet->SetHealth(NonConstAuraAttributeSet->GetHealth()+500.f);
				Destroy();
			}
		}
	}
}

void AAuraEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,int32 OtherBodyIndex)
{
	
}


void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this,&AAuraEffectActor::OnOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this,&AAuraEffectActor::EndOverlap);
}


