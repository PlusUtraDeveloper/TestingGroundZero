// Fill out your copyright notice in the Description page of Project Settings.

#include "TestingGroundZero.h"
#include "AIController.h"
#include "PatrolRoute.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ChooseNextWaypoint.h"




EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get Patrol Points
	auto AIController = OwnerComp.GetAIOwner();
	auto PatrolRoutes = AIController->GetPawn()->FindComponentByClass<UPatrolRoute>();
	auto PatrolPoints = PatrolRoutes->GetPatrolPoints();
	if (!ensure(PatrolRoutes)) { return EBTNodeResult::Failed; }
	if (PatrolPoints.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Guard missing a patrol route."));
		return EBTNodeResult::Failed;
	}
	// Set Next Waypoint
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);

	// Cycle Index
	auto NewIndex = (Index + 1) % PatrolPoints.Num();
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NewIndex);


	return EBTNodeResult::Succeeded;
}