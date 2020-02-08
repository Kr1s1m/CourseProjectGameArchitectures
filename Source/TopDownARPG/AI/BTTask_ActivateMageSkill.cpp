// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ActivateMageSkill.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackBoardKeyAllTypes.h"
#include "Characters/TopDownARPGCharacter.h"
#include "Controllers/MageAIController.h"
#include "TopDownARPG.h"


EBTNodeResult::Type UBTTask_ActivateMageSkill::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMageAIController* MageAIController = Cast<AMageAIController>(OwnerComp.GetOwner());
	if (IsValid(MageAIController) == false)
	{
		return EBTNodeResult::Failed;
	}

	APawn* EnemyPawn = MageAIController->GetPawn();
	if (IsValid(EnemyPawn) == false)
	{
		return EBTNodeResult::Failed;
	}

    FVector AimLocation = EnemyPawn->GetActorLocation() + EnemyPawn->GetActorForwardVector() * 100.0f;

	ATopDownARPGCharacter* targetChar = Cast<ATopDownARPGCharacter>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(MageAIController->TargetID));

	if (IsValid(targetChar))
	{
		AimLocation = targetChar->GetActorLocation();
	}


	MageAIController->ActivateAbility(AimLocation);

	return EBTNodeResult::Succeeded;
}
