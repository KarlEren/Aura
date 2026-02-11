


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

void AAuraCharacterBase::InitPrimaryAttributes()
{
	if (!AbilitySystemComponent)
	{
		UE_LOG(LogTemp,Error,TEXT("ASC Invalid"));
		return;
	}
	if (!PrimaryAttributes)
	{
		UE_LOG(LogTemp,Error,TEXT("GE Primary Invalid"));
		return;
	}
	FGameplayEffectContextHandle GameplayEffectContext =AbilitySystemComponent->MakeEffectContext();
	GameplayEffectContext.AddSourceObject(this);
	const FGameplayEffectSpecHandle GameplayEffectSpec = AbilitySystemComponent->MakeOutgoingSpec(PrimaryAttributes,1.f,GameplayEffectContext);
	const FActiveGameplayEffectHandle ActiveGameplayEffectHandle=AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*GameplayEffectSpec.Data.Get());
}


