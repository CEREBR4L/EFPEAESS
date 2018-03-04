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

	MinExtent = FVector(0, -2000, 0);
	MaxExtent = FVector(4000, 2000, 0);
	NavigationBoundsOffset = FVector(2000, 0, 0);
}

void ATile::SetPool(UActorPool* InPool) {
	Pool = InPool;

	PositionNavMeshVolume();
}

void ATile::PositionNavMeshVolume()
{
	NavMeshBoundsVolume = Pool->Checkout();

	if (NavMeshBoundsVolume == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("[%s] Not enough actors in pool"), *GetName())
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("[%s] Checked out: [%s]"), *GetName(), *NavMeshBoundsVolume->GetName())
	NavMeshBoundsVolume->SetActorLocation(GetActorLocation() + NavigationBoundsOffset);
	GetWorld()->GetNavigationSystem()->Build();
}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn, int MaxSpawn, float Radius, float MinScale, float MaxScale) {

	TArray<FSpawnPosition> SpawnPositions = RandomSpawnPositions(MinSpawn, MaxSpawn, Radius, MinScale, MaxScale);

	for (FSpawnPosition SpawnPosition : SpawnPositions) {
		PlaceActor(ToSpawn, SpawnPosition);
	}
}

void ATile::PlaceAIPawns(TSubclassOf<APawn> ToSpawn, int MinSpawn, int MaxSpawn, float Radius){
	
	TArray<FSpawnPosition> SpawnPositions = RandomSpawnPositions(MinSpawn, MaxSpawn, Radius, 1, 1);
	
	for (FSpawnPosition SpawnPosition : SpawnPositions) {
		PlaceAIPawn(ToSpawn, SpawnPosition);
		
	}
}

TArray<FSpawnPosition> ATile::RandomSpawnPositions(int MinSpawn, int MaxSpawn, float Radius, float MinScale, float MaxScale) {
	TArray<FSpawnPosition> SpawnPositions;

	int numberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);

	for (size_t i = 0; i < numberToSpawn; i++) {
		FSpawnPosition SpawnPosition;
		SpawnPosition.Scale = FMath::RandRange(MinScale, MaxScale);

		bool GotLocation = GetEmptyLocation(SpawnPosition.Location, Radius * SpawnPosition.Scale);
		if (GotLocation) {
			SpawnPosition.Rotation = FMath::RandRange(-180.0f, 180.0f);
			SpawnPositions.Add(SpawnPosition);
		}
	}

	return SpawnPositions;
}

bool ATile::GetEmptyLocation(FVector& outLocation, float Radius) {

	for (size_t i = 0; i < 15; i++) {
		FVector Location = FMath::RandPointInBox(FBox(MinExtent, MaxExtent));

		if (CanSpawnAtLocation(Location, Radius)) {
			outLocation = Location;
			return true;
		}
	}

	return false;
}

void ATile::PlaceActor(TSubclassOf<AActor> ToSpawn, const FSpawnPosition& SpawnPosition){
	AActor* Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);
	Spawned->SetActorRelativeLocation(SpawnPosition.Location);
	Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	Spawned->SetActorRotation(FRotator(0, SpawnPosition.Rotation, 0));
	Spawned->SetActorScale3D(FVector(SpawnPosition.Scale));
}

void ATile::PlaceAIPawn(TSubclassOf<APawn> ToSpawn, FSpawnPosition SpawnPosition)
{
	APawn* Pawn = GetWorld()->SpawnActor<APawn>(ToSpawn);
	Pawn->SetActorRelativeLocation(SpawnPosition.Location);
	Pawn->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	Pawn->SetActorRotation(FRotator(0, SpawnPosition.Rotation, 0));
	Pawn->SpawnDefaultController();
	Pawn->Tags.Add(FName("Enemy"));
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

