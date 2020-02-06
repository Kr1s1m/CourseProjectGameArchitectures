// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "TopDownARPG/Characters/TopDownARPGCharacter.h"
#include "TopDownARPG.h"
#include "SpawnPortal.generated.h"





UCLASS()
class TOPDOWNARPG_API ASpawnPortal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnPortal();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(VisibleAnywhere, Category = Gameplay)
	class UArrowComponent* ArrowComponent;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ATopDownARPGCharacter> slot0;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class ATopDownARPGCharacter> slot1;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class ATopDownARPGCharacter> slot2;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	bool SpawnActorFromPortalSlot(int slotNumber);

};
