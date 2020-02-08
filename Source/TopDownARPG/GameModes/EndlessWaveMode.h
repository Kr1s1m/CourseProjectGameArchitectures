// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameModes/TopDownARPGGameMode.h"
#include <TopDownARPG\Spawnpoints\SpawnPortal.h>
#include "EndlessWaveMode.generated.h"


/**
 * 
 */
UCLASS()
class TOPDOWNARPG_API AEndlessWaveMode : public ATopDownARPGGameMode
{
	GENERATED_BODY()

		UPROPERTY(EditDefaultsOnly)
		class UDataTable* wavesDT;

	int totalWaves;

	int currentWave;

	int enemiesInCurrentWave;

	int enemiesToSpawn;


	UPROPERTY(EditAnywhere)
		float spawnInterval = 2.0f;

	FTimerHandle SpawnTimerHandle;

	TArray<ASpawnPortal*> portals;

	TArray<int> currentSpawnQueue;

	int currentSpawnQueueFront;

	TArray<TArray<FString>> waveData;

	TArray<ASpawnPortal*> getPortalsFromWorld();

	ASpawnPortal* getRandomPortal();

	int countActorsInWorld()const;

	void generateSpawnQueueForCurrentWave();

	void readDataTable();

	UFUNCTION()
		void activateSpawner();

public:


	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
		int getCurrentWave() const;

	UFUNCTION(BlueprintCallable)
		int getEnemiesInCurrentWave() const;

	UFUNCTION(BlueprintCallable)
		int getIncomingEnemies() const;

	UFUNCTION(BlueprintCallable)
		int calculateEnemiesRemaining() const;
	
};
