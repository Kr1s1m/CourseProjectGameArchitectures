// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnPortal.h"
#include "Characters\TopDownARPGWarriorEnemy.h"
#include "Engine/World.h"

// Sets default values
ASpawnPortal::ASpawnPortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	PrimaryActorTick.bCanEverTick = true;
	


}

// Called when the game starts or when spawned
void ASpawnPortal::BeginPlay()
{
	Super::BeginPlay();
	
}

bool ASpawnPortal::SpawnActorFromPortalSlot(int slotNumber)
{
	

	UWorld* World = GetWorld();

	if (IsValid(World) == false)
	{
		UE_LOG(LogTopDownARPG, Error, TEXT("ASpawnPortal::SpawnActor IsValid(World) == false"));
	}


	


	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector Direction = GetActorForwardVector();
	Direction.Z = 0.0f;
	Direction.Normalize();

	FVector SpawnLocation = GetActorLocation() + Direction * 100.0f;

	TSubclassOf<class ATopDownARPGCharacter> spawnType;
	
	if (slotNumber == 0)
		spawnType = slot0;
	else if (slotNumber == 1)
		spawnType = slot1;
	else
		spawnType = slot2;


	AActor* spawnedActor = World->SpawnActor<AActor>(spawnType, SpawnLocation, Direction.Rotation(), SpawnParameters);

	if (IsValid(spawnedActor) == false)
	{
		UE_LOG(LogTopDownARPG, Error, TEXT("ASpawnPortal::SpawnActor IsValid(spawnedActor) == false"));
		return false;
	}
	return true;
	
}

// Called every frame
void ASpawnPortal::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);


}

