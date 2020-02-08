// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MageAIController.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNARPG_API AMageAIController : public AAIController
{
	GENERATED_BODY()
		

	AMageAIController();

	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(EditDefaultsOnly)
		class UBehaviorTree* BehaviourTree;

	UPROPERTY()
		class UBlackboardComponent* BlackboardComponent;

	UPROPERTY()
		class UBehaviorTreeComponent* BehaviourTreeComponent;

	public:
	void ActivateAbility(FVector AimLocation);
};
