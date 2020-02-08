// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_CheckForAlly.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackBoardKeyAllTypes.h"
#include "Characters/TopDownARPGCharacter.h"
#include "Controllers/PriestAIController.h"
#include "EngineUtils.h"
#include "TopDownARPG.h"


UBTService_CheckForAlly::UBTService_CheckForAlly()
{
	bCreateNodeInstance = true;
}

void UBTService_CheckForAlly::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	APriestAIController* PriestAIController = Cast<APriestAIController>(OwnerComp.GetAIOwner());

	if (IsValid(PriestAIController))
	{

		UWorld* World = GetWorld();

		

		if (IsValid(World))
		{



			for (TActorIterator<ATopDownARPGCharacter> characterIterator = TActorIterator<ATopDownARPGCharacter>(World); characterIterator; ++characterIterator)
			{

				if (IsValid(*characterIterator))
				{
					if ( characterIterator->isDamaged() && *characterIterator != World->GetFirstPlayerController()->GetPawn())
					{
						ATopDownARPGCharacter*  targetChar = Cast<ATopDownARPGCharacter>(*characterIterator);

						if (IsValid(targetChar) && targetChar)
						{
							OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(PriestAIController->AllyID, targetChar);
						}


						break;
					}
					else
					{
						continue;
					}


				}

			}
		}

		
	}
}
