// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_CheckForAlly.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNARPG_API UBTService_CheckForAlly : public UBTService
{
	GENERATED_BODY()
public:

	UBTService_CheckForAlly();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
