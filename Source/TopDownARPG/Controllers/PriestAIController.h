// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PriestAIController.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNARPG_API APriestAIController : public AAIController
{
	GENERATED_BODY()

	APriestAIController();
	
	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(EditDefaultsOnly)
		class UBehaviorTree* BehaviourTree;

	UPROPERTY()
		class UBlackboardComponent* BlackboardComponent;

	UPROPERTY()
		class UBehaviorTreeComponent* BehaviourTreeComponent;

public:

	UPROPERTY(EditDefaultsOnly)
		float maxRange;

	void ActivateAbility(FVector AimLocation);

	uint8 AllyID;

};
