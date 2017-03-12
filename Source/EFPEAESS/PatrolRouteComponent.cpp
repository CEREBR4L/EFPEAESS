// Fill out your copyright notice in the Description page of Project Settings.

#include "EFPEAESS.h"
#include "PatrolRouteComponent.h"


TArray<AActor*> UPatrolRouteComponent::GetPatrolRoute() const
{
	return PatrolRoute;
}

