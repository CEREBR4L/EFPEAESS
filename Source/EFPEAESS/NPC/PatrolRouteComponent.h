// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "PatrolRouteComponent.generated.h"

/**
* A routing componenent to dictate an AI's next target and overall route.
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EFPEAESS_API UPatrolRouteComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	TArray<AActor*> GetPatrolRoute() const;

private:	

	UPROPERTY(EditInstanceOnly, Category = "Patrol")
	TArray<AActor*> PatrolRoute;
	
};
