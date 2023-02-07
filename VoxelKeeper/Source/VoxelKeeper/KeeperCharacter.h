// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "KeeperCharacter.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class VOXELKEEPER_API AKeeperCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AKeeperCharacter();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    // ----- Input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* KeeperCharacterMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* MoveInputAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* LookInputAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* PrimaryTappedInputAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* PrimaryHeldInputAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* SecondayTappedInputAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* SecondayHeldInputAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* SpeedModifierInputAction;
	
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	
	void PrimaryTappedAction(const FInputActionValue& Value);
	void PrimaryHeldAction(const FInputActionValue& Value);
	void SecondayTappedAction(const FInputActionValue& Value);
	void SecondayHeldAction(const FInputActionValue& Value);

	
	void ModifyMoveSpeed(const FInputActionValue& Value);

private:

	APlayerController* KeeperPlayerController;
	
	// ----- Movement
	UPROPERTY(EditAnywhere)
	float BaseMoveSpeed = 100.0f;

	UPROPERTY(EditAnywhere)
	float BoostedMoveSpeed = 200.0f;

	// ----- Rotation
	bool bAllowRotation = false;
};
