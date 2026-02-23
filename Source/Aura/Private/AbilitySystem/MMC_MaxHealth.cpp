// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/MMC_MaxHealth.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{
	VigorDef.bSnapshot = false;
	VigorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	VigorDef.AttributeToCapture = UAuraAttributeSet::GetVigorAttribute();
	RelevantAttributesToCapture.Add(VigorDef);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer *SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	if (!SourceTags)
	{
		return Super::CalculateBaseMagnitude_Implementation(Spec);
	}
	const FGameplayTagContainer *TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	if (!TargetTags)
	{
		return Super::CalculateBaseMagnitude_Implementation(Spec);
	}
	FAggregatorEvaluateParameters EvaluateParams;
	EvaluateParams.SourceTags = SourceTags;
	EvaluateParams.TargetTags = TargetTags;
	float Vigor  = 0.f;
	GetCapturedAttributeMagnitude(VigorDef,Spec,EvaluateParams,Vigor);
	Vigor = FMath::Max<float>(Vigor,0.f);
	TScriptInterface<ICombatInterface> CombatInterface = Spec.GetContext().GetSourceObject();
	if (!CombatInterface)
	{
		return Super::CalculateBaseMagnitude_Implementation(Spec);
	}
	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();
	return 80.f + 2.5f*Vigor + 10*PlayerLevel;	
}
