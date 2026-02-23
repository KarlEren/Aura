// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/MMC_MaxMana.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxMana::UMMC_MaxMana()
{
	IntDef.bSnapshot = false;
	IntDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	IntDef.AttributeToCapture = UAuraAttributeSet::GetIntelligenceAttribute();
	RelevantAttributesToCapture.Add(IntDef);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
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
	GetCapturedAttributeMagnitude(IntDef,Spec,EvaluateParams,Vigor);
	Vigor = FMath::Max<float>(Vigor,0.f);
	TScriptInterface<ICombatInterface> CombatInterface = Spec.GetContext().GetSourceObject();
	if (!CombatInterface)
	{
		return Super::CalculateBaseMagnitude_Implementation(Spec);
	}
	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();
	return 80.f + 2.5f*Vigor + 10*PlayerLevel;
}
