// Fill out your copyright notice in the Description page of Project Settings.

#include "EFPEAESS.h"
#include "ActorPool.h"


// Sets default values for this component's properties
UActorPool::UActorPool()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

AActor* UActorPool::Checkout() {
	return Pool.Num() == 0 ? nullptr : Pool.Pop();
}

void UActorPool::Return(AActor* ActorToReturn) {
	if (ActorToReturn == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Null actor provided to ActorPool."))
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Actor returned to ActorPool: %s"), *ActorToReturn->GetName())
	Pool.Push(ActorToReturn);
}

void UActorPool::Add(AActor* ActorToAdd) {
	Return(ActorToAdd);
}