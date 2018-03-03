// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EFPEAESSGameMode.h"
#include "InfiniteTerrainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class EFPEAESS_API AInfiniteTerrainGameMode : public AEFPEAESSGameMode
{
	GENERATED_BODY()
	
public:

	AInfiniteTerrainGameMode();

	UFUNCTION(BlueprintCallable, Category = "Bounds Pool")
	void PopulateBoundVolumePool();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NavMesh Pool")
	class UActorPool* NavMeshBoundsVolumePool;

private:

	void AddToPool(class ANavMeshBoundsVolume *VolumeToAdd);
	
};
