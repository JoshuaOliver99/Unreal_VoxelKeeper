// Fill out your copyright notice in the Description page of Project Settings.


#include "KeeperPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "KeeperCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

void AKeeperPlayerController::ReturnToKeeperCharacter()
{
	ACharacter* OldCharacter = GetCharacter();
	if (OldCharacter == nullptr)
	{
		return;
	}
	
	UnPossess();

	OldCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	// possess our new actor                              
	Possess(Cast<APawn>(KeeperCharacter)); 
}

void AKeeperPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Set the KeeperCharacter ref
	KeeperCharacter = Cast<AKeeperCharacter>(GetCharacter());
}
