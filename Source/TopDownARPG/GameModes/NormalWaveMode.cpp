// Fill out your copyright notice in the Description page of Project Settings.


#include "NormalWaveMode.h"
#include "Engine\World.h"
#include "Spawnpoints\SpawnPortal.h"
#include "Characters\TopDownARPGWarriorEnemy.h"
#include "EngineUtils.h"
#include <algorithm>
#include <random>
#include <time.h>

TArray<ASpawnPortal*> ANormalWaveMode::getPortalsFromWorld()
{
	UWorld* World = GetWorld();

	if(IsValid(World))
	{ 

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

		return {};
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

void ANormalWaveMode::generateSpawnQueueForCurrentWave()
{
	if (currentWave < 0 || currentWave > waveData.Num() - 1)
		return;

	int currentRowIndex = currentWave;
	int enemiesInSpawnQue = 0;

	TArray<int> currentRow;

	std::vector<int> temp;

	for (int i = 1; i < waveData[currentRowIndex].Num(); i++)
		currentRow.Add(FCString::Atoi(*waveData[currentRowIndex][i]));

	int currentSlot = 0;

	for (auto& number : currentRow)
	{
		if (number != 0)
		{
			for (int i = 0; i < number; i++)
			{
				temp.push_back(currentSlot);
				enemiesInSpawnQue++;
			}
		}

		currentSlot++;
	}

	std::random_shuffle(temp.begin(), temp.end());

	for (int num : temp)
		currentSpawnQueue.Add(num);

	//std::random_shuffle(currentSpawnQueue.begin(), currentSpawnQueue.end());

	currentSpawnQueueFront = 0;

	enemiesToSpawn = enemiesInSpawnQue;
}


void ANormalWaveMode::readDataTable()
{
	if (IsValid(wavesDT))
	{

		if (wavesDT->GetTableData().Num() > 0)
		{
			waveData = wavesDT->GetTableData();
			totalWaves = waveData.Num() - 1;
		}

	}
	
	

}

void ANormalWaveMode::activateSpawner()
{
	if (enemiesToSpawn > 0 && currentSpawnQueue.Num() > 0 && currentSpawnQueueFront < currentSpawnQueue.Num())
	{
		getRandomPortal()->SpawnActorFromPortalSlot(currentSpawnQueue[currentSpawnQueueFront]);
			currentSpawnQueueFront++;
			enemiesToSpawn--;
	}
	else if (countActorsInWorld() == 1 && currentWave < totalWaves)
	{
		currentWave++;
		currentSpawnQueue.Empty();
		generateSpawnQueueForCurrentWave();
	}
}


void ANormalWaveMode::BeginPlay()
{
	readDataTable();

	currentWave = 1;

	generateSpawnQueueForCurrentWave();

	portals = getPortalsFromWorld();

	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &ANormalWaveMode::activateSpawner, spawnInterval, true, spawnInterval);


	
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
