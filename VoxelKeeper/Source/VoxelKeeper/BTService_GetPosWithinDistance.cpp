// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_GetPosWithinDistance.h"

//#include "AIController.h"
//#include "BehaviorTree/BlackboardComponent.h"
//
//UBTService_GetPosWithinDistance::UBTService_GetPosWithinDistance()
//{
//	NodeName = TEXT("Get a Position Witin Distance");
//}
//
//void UBTService_GetPosWithinDistance::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
//{
//	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
//
//	
//	//OwnerComp.GetOwner()->GetActorLocation()
//
//	FVector TargetLocation = FVector(
//		OwnerComp.GetOwner()->GetActorLocation() * FVector(100,0,0));
//	
//
//	if (OwnerComp.GetAIOwner())
//	{
//		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), TargetLocation);
//	}
//	else
//	{
//		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
//	}
//}
