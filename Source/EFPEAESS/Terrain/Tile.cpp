// Fill out your copyright notice in the Description page of Project Settings.

#include "EFPEAESS.h"
#include "Tile.h"
#include "DrawDebugHelpers.h"
#include "ActorPool.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATile::SetPool(UActorPool* InPool) {
	Pool = InPool;

	PositionNavMeshVolume();
}

void ATile::PositionNavMeshVolume()
{
	NavMeshBoundsVolume = Pool->Checkout();

	if (NavMeshBoundsVolume == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Not enough actors in pool"))
		return;
	}

	NavMeshBoundsVolume->SetActorLocation(GetActorLocation());
}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn, int MaxSpawn, float Radius, float MinScale, float MaxScale) {

	int numberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);

	for (size_t i = 0; i < numberToSpawn; i++) {
		FVector SpawnPoint;
		float RandScale = FMath::RandRange(MinScale, MaxScale);

		bool GotLocation = GetEmptyLocation(SpawnPoint, Radius * RandScale);
		if (GotLocation) {
			float RandRotation = FMath::RandRange(-180.0f, 180.0f);
			PlaceActor(ToSpawn, SpawnPoint, RandRotation, RandScale);
		}
	}
}

bool ATile::GetEmptyLocation(FVector& outLocation, float Radius) {

	for (size_t i = 0; i < 15; i++) {
		FVector Location = FMath::RandPointInBox(FBox(FVector(0, -2000, 0), FVector(4000, 2000, 0)));

		if (CanSpawnAtLocation(Location, Radius)) {
			outLocation = Location;
			return true;
		}
	}

	return false;
}

void ATile::PlaceActor(TSubclassOf<AActor> ToSpawn, FVector SpawnPoint, float Rotation, float Scale){
	AActor* Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);
	Spawned->SetActorRelativeLocation(SpawnPoint);
	Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	Spawned->SetActorRotation(FRotator(0, Rotation, 0));
	Spawned->SetActorScale3D(FVector(Scale));
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();

	//CastSphere(GetActorLocation(), 300);

}

void ATile::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	Pool->Return(NavMeshBoundsVolume);
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ATile::CanSpawnAtLocation(FVector Location, float Radius) {
	FHitResult HitResult;
	FVector GlobalLocation = ActorToWorld().TransformPosition(Location);

	bool HasHit = GetWorld()->SweepSingleByChannel(HitResult, GlobalLocation, GlobalLocation, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(Radius));

	if (false) { // to add ue4 property for debug...
		FColor colour = HasHit ? FColor::Red : FColor::Green;
		DrawDebugCapsule(GetWorld(), GlobalLocation, 0, Radius, FQuat::Identity, colour, true, 100);
	}

	return !HasHit;
}

