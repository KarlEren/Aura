// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "GameFramework/Character.h"
#include "Interaction/CombatInterface.h"
#include "AuraCharacterBase.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter,public IAbilitySystemInterface,public ICombatInterface
{
	GENERATED_BODY()

public:
	
	AAuraCharacterBase();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	UAttributeSet* GetAttributeSet()const{return AttributeSet;}

	virtual void InitAbilityActorInfo();



	virtual void InitDefaultAttributes(TSubclassOf<UGameplayEffect>& GameplayEffect,float Level);

	virtual void ActivateAbilities();
	
protected:

	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere,Category="Combat")
	TObjectPtr<USkeletalMeshComponent>Weapon;
	
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent>AbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<UAttributeSet>AttributeSet;


	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<UGameplayEffect> PrimaryAttributes;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<UGameplayEffect> SecondaryAttributes;


	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<UGameplayEffect> VitalAttributes;
	
};
