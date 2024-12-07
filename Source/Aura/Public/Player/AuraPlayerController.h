

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "AuraPlayerController.generated.h"


class UInputMappingContext;//为了使用增强输入，必须显式声明，同时在.build.cs中添加“EnhancedInput”

UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AAuraPlayerController();
protected:
	virtual void BeginPlay() override;
private:
	TObjectPtr<UInputMappingContext>AuraContext;
};
