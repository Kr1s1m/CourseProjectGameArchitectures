// Fill out your copyright notice in the Description page of Project Settings.


#include "NormalWaveMode.h"
#include "Engine\World.h"
#include "Spawnpoints\SpawnPortal.h"
#include "Characters\TopDownARPGWarriorEnemy.h"
#include "EngineUtils.h"
#include <time.h>

TArray<ASpawnPortal*> ANormalWaveMode::getPortalsFromWorld()
{
	UWorld* World = GetWorld();

	TArray<ASpawnPortal*> portalsFound;

	for (TActorIterator<ASpawnPortal> portalIterator = TActorIterator<ASpawnPortal>(World); portalIterator; ++portalIterator)
	{

		if (IsValid(*portalIterator))
		{
			portalsFound.Add(*portalIterator);
			
		}

	}

	return portalsFound;
}

ASpawnPortal* ANormalWaveMode::getRandomPortal()
{
	srand(time(NULL));

	int portalCount = portals.Num();
	int randomIndex = rand() % portalCount;
		
	if (randomIndex < portalCount && portals.Num() > 0)
		return portals[randomIndex];
	else
		return nullptr;
}

int ANormalWaveMode::countActorsInWorld()const
{
	int charCount = 0;

	UWorld* World = GetWorld();

	for (TActorIterator<ATopDownARPGCharacter> characterIterator = TActorIterator<ATopDownARPGCharacter>(World); characterIterator; ++characterIterator)
	{

		if (IsValid(*characterIterator))
		{
			charCount++;

		}

	}

	return charCount;
}

int ANormalWaveMode::generateNewEnemyCount()
{	
	int newValue = enemiesInCurrentWave  + 1;

	enemiesInCurrentWave = newValue;
	
	return newValue;
}

void ANormalWaveMode::activateSpawner()
{
	if (enemiesToSpawn > 0)
	{
		srand(time(NULL));
		int randomSlot = rand() % 3;

		getRandomPortal()->SpawnActorFromPortalSlot(randomSlot);

		enemiesToSpawn--;
	}
	else if (countActorsInWorld() == 1 && currentWave <= totalWaves)
	{
		enemiesToSpawn = generateNewEnemyCount();
		currentWave++;
	}


}

void ANormalWaveMode::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);

	
}

void ANormalWaveMode::BeginPlay()
{
	enemiesToSpawn = enemiesInCurrentWave;

	portals = getPortalsFromWorld();

	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &ANormalWaveMode::activateSpawner,5.0f, true, 5.0f);


	
}

int ANormalWaveMode::getCurrentWave() const
{
	return currentWave;
}

int ANormalWaveMode::getEnemiesInCurrentWave() const
{
	return enemiesInCurrentWave;
}

int ANormalWaveMode::getIncomingEnemies() const
{
	return enemiesToSpawn;
}

int ANormalWaveMode::calculateEnemiesRemaining() const
{
	return countActorsInWorld() - 1;

}
