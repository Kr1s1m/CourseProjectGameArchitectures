// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ActivatePriestSkill.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackBoardKeyAllTypes.h"
#include "Characters/TopDownARPGCharacter.h"
#include "Controllers/PriestAIController.h"
#include "TopDownARPG.h"


EBTNodeResult::Type UBTTask_ActivatePriestSkill::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APriestAIController* PriestAIController = Cast<APriestAIController>(OwnerComp.GetOwner());
	if (IsValid(PriestAIController) == false)
	{
		return EBTNodeResult::Failed;
	}

	APawn* PriestPawn = PriestAIController->GetPawn();
	if (!IsValid(PriestPawn))
	{
		return EBTNodeResult::Failed;
	}

	FVector AimLocation = PriestPawn->GetActorLocation() + PriestPawn->GetActorForwardVector() * 100.0f;

	ATopDownARPGCharacter* allyChar = Cast<ATopDownARPGCharacter>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(PriestAIController->AllyID));

	if (IsValid(allyChar))
	{
		AimLocation = allyChar->GetActorLocation();
	}

	PriestAIController->ActivateAbility(AimLocation);

	return EBTNodeResult::Succeeded;
}
