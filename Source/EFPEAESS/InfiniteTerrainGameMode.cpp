// Fill out your copyright notice in the Description page of Project Settings.

#include "EFPEAESS.h"
#include "InfiniteTerrainGameMode.h"
#include "AI/Navigation/NavMeshBoundsVolume.h"
#include "EngineUtils.h"
#include "ActorPool.h"

AInfiniteTerrainGameMode::AInfiniteTerrainGameMode() {
	NavMeshBoundsVolumePool = CreateDefaultSubobject<UActorPool>(FName("Nav Mesh Bounds Pool"));
}

void AInfiniteTerrainGameMode::PopulateBoundVolumePool() {
	auto VolumeIterator = TActorIterator<ANavMeshBoundsVolume>(GetWorld());

	while (VolumeIterator) {
		AddToPool(*VolumeIterator);
		++VolumeIterator;
	}
}

void AInfiniteTerrainGameMode::AddToPool(class ANavMeshBoundsVolume *VolumeToAdd) {
	UE_LOG(LogTemp, Warning, TEXT("FOUND ACTOR: %s"), *VolumeToAdd->GetName())
}
