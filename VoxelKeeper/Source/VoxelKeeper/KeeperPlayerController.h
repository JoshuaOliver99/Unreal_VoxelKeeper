// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "KeeperPlayerController.generated.h"


class AKeeperCharacter;

/**
 * 
 */
UCLASS()
class VOXELKEEPER_API AKeeperPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void ReturnToKeeperCharacter();

protected:
	virtual void BeginPlay() override;
	
private:
	// Pointer to the players controllable KeeperCharacter
	AKeeperCharacter* KeeperCharacter;
};
