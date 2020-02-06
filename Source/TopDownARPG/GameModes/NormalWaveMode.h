// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Spawnpoints/SpawnPortal.h"
#include "NormalWaveMode.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNARPG_API ANormalWaveMode : public AGameModeBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	int totalWaves = 7;

	UPROPERTY(EditAnywhere)
	int currentWave = 1;

	UPROPERTY(EditAnywhere)
	int enemiesInCurrentWave = 5;

	int enemiesToSpawn;


	UPROPERTY(EditAnywhere)
	float spawnInterval;

	FTimerHandle SpawnTimerHandle;

	

	TArray<ASpawnPortal*> portals;

	TArray<ASpawnPortal*> getPortalsFromWorld();

	ASpawnPortal* getRandomPortal();

	int countActorsInWorld()const;

	int generateNewEnemyCount();

	UFUNCTION()
	void activateSpawner();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

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
