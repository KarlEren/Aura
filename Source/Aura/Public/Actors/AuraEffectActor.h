// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"


class UAbilitySystemComponent;
class UGameplayEffect;

UENUM(BlueprintType)
enum class EAuraEffectType : uint8
{
	Health=0,
	Mana,
};


UENUM(BlueprintType)
enum class EAuraApplyEffectPolicy:uint8
{
	ApplyOnOverlap=0,
	ApplyOnEndOverlap,
	DoNotApply,
};

UENUM(BlueprintType)
enum class EAuraRemoveEffectPolicy:uint8
{
	RemoveOnEndOverlap=0,
	DoNotRemove,
};

class USphereComponent;

UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAuraEffectActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ApplyEffect(AActor *TargetActor,TSubclassOf<UGameplayEffect>GameplayEffectClass);

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor,TSubclassOf<UGameplayEffect>GameplayEffectClass);

	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor *TargetActor);

	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor *TargetActor);
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	bool bDestroyAfterApplying = false;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	EAuraApplyEffectPolicy InstantPolicy = EAuraApplyEffectPolicy::DoNotApply;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	EAuraApplyEffectPolicy DurationPolicy = EAuraApplyEffectPolicy::DoNotApply;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	EAuraApplyEffectPolicy InfinitePolicy = EAuraApplyEffectPolicy::DoNotApply;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	EAuraRemoveEffectPolicy InfiniteRemovePolicy = EAuraRemoveEffectPolicy::RemoveOnEndOverlap;

	TMap<FActiveGameplayEffectHandle,UAbilitySystemComponent*> ActiveEffectHandles;
	
};
