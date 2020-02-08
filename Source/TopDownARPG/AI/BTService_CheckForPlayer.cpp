// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_CheckForPlayer.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackBoardKeyAllTypes.h"
#include "Characters/TopDownARPGCharacter.h"
#include "Controllers/MageAIController.h"
#include "TopDownARPG.h"


UBTService_CheckForPlayer::UBTService_CheckForPlayer()
{
	bCreateNodeInstance = true;
}

void UBTService_CheckForPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AMageAIController* MageAIController = Cast<AMageAIController>(OwnerComp.GetAIOwner());

	if (IsValid(MageAIController))
	{
		ATopDownARPGCharacter* targetChar = Cast<ATopDownARPGCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

		if (IsValid(targetChar))
		{
			OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(MageAIController->TargetID, targetChar);
		}
	}
}