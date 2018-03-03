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

	UFUNCTION(BlueprintCallable, Category = "Bounds Pool")
	void PopulateBoundVolumePool();

private:

	void AddToPool(class ANavMeshBoundsVolume *VolumeToAdd);
	
};
