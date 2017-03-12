// Fill out your copyright notice in the Description page of Project Settings.

#include "EFPEAESS.h"
#include "ChooseNextWaypoint.h"
#include "AIController.h"
#include "PatrollingGuard.h" //TODO remove coupling
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	
	auto AIController = OwnerComp.GetAIOwner();
	auto ControlledPawn = AIController->GetPawn();
	auto PatrollingGuard = Cast<APatrollingGuard>(ControlledPawn);
	auto PatrolPoints = PatrollingGuard->PatrolRoute;

	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	BlackboardComp->SetValueAsObject(TargetKey.SelectedKeyName, PatrolPoints[Index]);

	auto NextIndex = (Index + 1) % PatrolPoints.Num();
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);

	//UE_LOG(LogTemp, Warning, TEXT("Target Index: %i"), Index)
	
	return EBTNodeResult::Succeeded;

}

