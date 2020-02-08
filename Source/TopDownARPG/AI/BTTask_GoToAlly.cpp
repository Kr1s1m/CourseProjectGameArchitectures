// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_GoToAlly.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackBoardKeyAllTypes.h"
#include "Characters/TopDownARPGCharacter.h"
#include "Controllers/PriestAIController.h"
#include "TopDownARPG.h"

EBTNodeResult::Type UBTTask_GoToAlly::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	APriestAIController* PriestAIController = Cast<APriestAIController>(OwnerComp.GetAIOwner());

	ATopDownARPGCharacter* targetChar = Cast<ATopDownARPGCharacter>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(PriestAIController->AllyID));

	if (IsValid(targetChar))
	{
		PriestAIController->MoveToActor(targetChar, PriestAIController->maxRange, true, true, true, 0, true);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
