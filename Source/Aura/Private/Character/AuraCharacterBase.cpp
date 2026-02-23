


#include "Character/AuraCharacterBase.h"


AAuraCharacterBase::AAuraCharacterBase()
{
 	
	PrimaryActorTick.bCanEverTick = false;
	Weapon=CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(),FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	
}

UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}


void AAuraCharacterBase::InitAbilityActorInfo()
{
}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAuraCharacterBase::InitDefaultAttributes(TSubclassOf<UGameplayEffect>& GameplayEffect, float Level)
{
	if (!AbilitySystemComponent)
	{
		UE_LOG(LogTemp,Error,TEXT("ASC Invalid"));
		return;
	}
	if (!GameplayEffect)
	{
		UE_LOG(LogTemp,Error,TEXT("GE Primary Invalid"));
		return;
	}
	FGameplayEffectContextHandle GameplayEffectContext =AbilitySystemComponent->MakeEffectContext();
	GameplayEffectContext.AddSourceObject(this);
	const FGameplayEffectSpecHandle GameplayEffectSpec = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffect,Level,GameplayEffectContext);
	const FActiveGameplayEffectHandle ActiveGameplayEffectHandle=AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*GameplayEffectSpec.Data.Get());
}

void AAuraCharacterBase::ActivateAbilities()
{
	InitDefaultAttributes(PrimaryAttributes,1.f);
	InitDefaultAttributes(SecondaryAttributes,1.f);
	InitDefaultAttributes(VitalAttributes,1.f);
}


