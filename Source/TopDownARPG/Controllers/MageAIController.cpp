// Fill out your copyright notice in the Description page of Project Settings.


#include "MageAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/TopDownARPGCharacter.h"
#include "TopDownARPG.h"

AMageAIController::AMageAIController()
{
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));
	BehaviourTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviourTree"));
}

void AMageAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (IsValid(BehaviourTree))
	{
		BlackboardComponent->InitializeBlackboard(*BehaviourTree->BlackboardAsset);
		TargetID = BlackboardComponent->GetKeyID("Target");

		BehaviourTreeComponent->StartTree(*BehaviourTree);

		
	}
}

void AMageAIController::ActivateAbility(FVector AimLocation)
{

	

	
	ATopDownARPGCharacter* MageEnemy = Cast<ATopDownARPGCharacter>(GetPawn());
	if (IsValid(MageEnemy) == false)
	{
		UE_LOG(LogTopDownARPG, Error, TEXT("AMageAIController::ActivateAbility IsValid(MageEnemy) == false"));
		return;
	}

	if (MageEnemy->AbilityInstances.Num() > 0)
	{

		

		int abilityIndex = 0;

		if (abilityIndex >= 0 && abilityIndex < MageEnemy->AbilityInstances.Num())
		{

			UAbility* Ability = MageEnemy->AbilityInstances[abilityIndex];
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
