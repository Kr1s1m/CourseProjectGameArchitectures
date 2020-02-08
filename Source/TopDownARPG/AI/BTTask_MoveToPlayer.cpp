// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MoveToPlayer.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackBoardKeyAllTypes.h"
#include "Characters/TopDownARPGCharacter.h"
#include "Controllers/MageAIController.h"
#include "TopDownARPG.h"

EBTNodeResult::Type UBTTask_MoveToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMageAIController* MageAIController = Cast<AMageAIController>(OwnerComp.GetAIOwner());

	ATopDownARPGCharacter* targetChar = Cast<ATopDownARPGCharacter>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(MageAIController->TargetID));

	if (IsValid(targetChar))
	{
		MageAIController->MoveToActor(targetChar, MageAIController->maxRange,  true, true, true, 0, true);

		return EBTNodeResult::Succeeded;
	}


	return EBTNodeResult::Failed;
}
