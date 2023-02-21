// Fill out your copyright notice in the Description page of Project Settings.


#include "AIControllerBase.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void AAIControllerBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AAIControllerBase::BeginPlay()
{
	Super::BeginPlay();

	if (AIBehavior != nullptr)
	{
		RunBehaviorTree(AIBehavior);

		//APawn* PlayerPawn =	UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		//GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
	}
}
