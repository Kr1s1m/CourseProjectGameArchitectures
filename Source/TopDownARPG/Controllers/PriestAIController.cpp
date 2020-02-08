// Fill out your copyright notice in the Description page of Project Settings.



#include "PriestAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/TopDownARPGCharacter.h"
#include "TopDownARPG.h"

APriestAIController::APriestAIController()
{
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));
	BehaviourTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviourTree"));
}

void APriestAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (IsValid(BehaviourTree))
	{
		BlackboardComponent->InitializeBlackboard(*BehaviourTree->BlackboardAsset);
		AllyID = BlackboardComponent->GetKeyID("Ally");

		BehaviourTreeComponent->StartTree(*BehaviourTree);


	}
}

void APriestAIController::ActivateAbility(FVector AimLocation)
{
	ATopDownARPGCharacter* PriestEnemy = Cast<ATopDownARPGCharacter>(GetPawn());

	if (IsValid(PriestEnemy) == false)
	{
		UE_LOG(LogTopDownARPG, Error, TEXT("AMageAIController::ActivateAbility IsValid(MageEnemy) == false"));
		return;
	}

	if (PriestEnemy->AbilityInstances.Num() > 0)
	{



		int abilityIndex = 0;

		if (abilityIndex >= 0 && abilityIndex < PriestEnemy->AbilityInstances.Num())
		{

			UAbility* Ability = PriestEnemy->AbilityInstances[abilityIndex];
			if (IsValid(Ability))
			{
				Ability->Activate(AimLocation);
			}
		}
		else
			UE_LOG(LogTopDownARPG, Error, TEXT("AMageAIController::ActivateAbility BAD INDEX"));
	}
	else
		UE_LOG(LogTopDownARPG, Error, TEXT("AMageAIController::ActivateAbility ABILITY ARRAY IS EMPTY"));

}
