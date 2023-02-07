// Fill out your copyright notice in the Description page of Project Settings.


#include "KeeperCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"


// Sets default values
AKeeperCharacter::AKeeperCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AKeeperCharacter::BeginPlay()
{
	Super::BeginPlay();

	
	// ----- Setup Input
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(KeeperCharacterMappingContext, 0);
		}
	}
}

void AKeeperCharacter::Move(const FInputActionValue& Value)
{
	const FVector CurrentValue = Value.Get<FVector>();

	// Forward
	if (CurrentValue.X != 0)
	{
		AddMovementInput(GetActorForwardVector() * CurrentValue.X);
	}

	// Lateral
	if (CurrentValue.Y != 0)
	{
		AddMovementInput(GetActorRightVector() * CurrentValue.Y);
	}

	// Vertical
	if (CurrentValue.Z != 0)
	{
		AddMovementInput(GetActorUpVector() * CurrentValue.Z);
	}
}

void AKeeperCharacter::Look(const FInputActionValue& Value)
{
	const FVector2d CurrentValue = Value.Get<FVector2d>();

	// Left/Right
	if (CurrentValue.X != 0)
	{
		AddControllerYawInput(CurrentValue.X);
	}

	// Up/Down
	if (CurrentValue.Y != 0)
	{
		AddControllerPitchInput(CurrentValue.Y);
	}
}

// Called every frame
void AKeeperCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AKeeperCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// ----- Setup Input
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AKeeperCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AKeeperCharacter::Look);
		
	}
}

