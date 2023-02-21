// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_GetNearbyPosition.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "NavigationSystem.h"


UBTTask_GetNearbyPosition::UBTTask_GetNearbyPosition()
{
	NodeName = TEXT("Get Nearby Position ");
}

EBTNodeResult::Type UBTTask_GetNearbyPosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	// TODO
	// - Remove hardcoded deviation amount and make it a BT variable
	//const FVector NewLocation = OwnerComp.GetOwner()->GetActorLocation() + FVector(200, 200,0);
	//OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), NewLocation);
	
	// TODO
	// This doesnt work (initializing UNavigationSystemV1)
	//FNavLocation ResultLocation;
	//const UNavigationSystemV1 NavigationSystemV1;
	//if (NavigationSystemV1.GetRandomReachablePointInRadius(OwnerComp.GetOwner()->GetActorLocation(), 500.f, ResultLocation))
	//{
	//	OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), ResultLocation);
	//	return EBTNodeResult::Succeeded;
	//}

	return EBTNodeResult::Failed; 
}
