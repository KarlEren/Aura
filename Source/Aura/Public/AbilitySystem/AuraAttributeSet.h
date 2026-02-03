// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AuraAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

USTRUCT(BlueprintType)
struct FAuraEffectProps
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAbilitySystemComponent* SourceASC = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* SourceAvatarActor = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AController* SourceController = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ACharacter* SourceCharacter = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAbilitySystemComponent* TargetASC = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* TargetAvatarActor = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AController* TargetController = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ACharacter* TargetCharacter = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayEffectContextHandle EffectContextHandle{};
};



/**
 * 
 */
UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:

	UAuraAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Health)

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth)const;

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,MaxHealth)
	
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)const;

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Mana)
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Mana)
	
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana)const;

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_MaxMana)
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,MaxMana)
	
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana)const;

protected:

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

private:

	void UpdateAuraEffectProps(const struct FGameplayEffectModCallbackData& Data,FAuraEffectProps& OutEffectProps)const;
	
};
