// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_GetNearbyPosition.generated.h"

/**
 * 
 */
UCLASS()
class VOXELKEEPER_API UBTTask_GetNearbyPosition : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_GetNearbyPosition();

private:


protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
