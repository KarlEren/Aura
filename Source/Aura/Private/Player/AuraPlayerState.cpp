// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerState.h"

#include "LevelEditor.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Net/UnrealNetwork.h"

AAuraPlayerState::AAuraPlayerState()
{
	NetUpdateFrequency=100;//服务器更新客户端的频率
	AbilitySystemComponent=CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");//赋值
	AbilitySystemComponent->SetIsReplicated(true);//设置可被服务器赋值
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);//设置复制模式为Mixed
	AttributeSet=CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
	
	
}




UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

int32 AAuraPlayerState::GetPlayerLevel() const
{
	return Level;
}

void AAuraPlayerState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AAuraPlayerState,Level)
}

void AAuraPlayerState::OnRep_Level(int32 OldLevel)
{
	
}
