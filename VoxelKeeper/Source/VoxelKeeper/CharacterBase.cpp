// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KeeperCharacter.h"
#include "KeeperPlayerController.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// ----- Setup InputAction Binds
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &ACharacterBase::Move);
		EnhancedInputComponent->BindAction(LookInputAction, ETriggerEvent::Triggered, this, &ACharacterBase::Look);
		
		EnhancedInputComponent->BindAction(PrimaryTappedInputAction, ETriggerEvent::Triggered, this, &ACharacterBase::PrimaryTappedAction);
		EnhancedInputComponent->BindAction(PrimaryHeldInputAction, ETriggerEvent::Triggered, this, &ACharacterBase::PrimaryHeldAction);
		EnhancedInputComponent->BindAction(PrimaryHeldInputAction, ETriggerEvent::Completed, this, &ACharacterBase::PrimaryHeldAction);
		
		EnhancedInputComponent->BindAction(SecondayTappedInputAction, ETriggerEvent::Triggered, this, &ACharacterBase::SecondaryTappedAction);
		EnhancedInputComponent->BindAction(SecondayHeldInputAction, ETriggerEvent::Triggered, this, &ACharacterBase::SecondaryHeldAction);
		EnhancedInputComponent->BindAction(SecondayHeldInputAction, ETriggerEvent::Completed, this, &ACharacterBase::SecondaryHeldAction);

		EnhancedInputComponent->BindAction(SpeedModifierInputAction, ETriggerEvent::Triggered, this, &ACharacterBase::ModifyMoveSpeed);
		EnhancedInputComponent->BindAction(SpeedModifierInputAction, ETriggerEvent::Completed, this, &ACharacterBase::ModifyMoveSpeed);
	}
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

	// ----- Setup InputMappingContext
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PosessionMappingContext, 0);
		}
	}

	// ----- Init settings
	//GetCharacterMovement()->MaxFlySpeed = BaseMoveSpeed;

	PossessedPlayerController = Cast<APlayerController>(GetController());
}

void ACharacterBase::Move(const FInputActionValue& Value)
{
	const FVector CurrentValue = Value.Get<FVector>();

	// Forward
	if (CurrentValue.X != 0)
	{
		AddMovementInput(GetActorForwardVector(), CurrentValue.X); //* CurrentMoveSpeed * GetWorld()->GetDeltaSeconds());
	}

	// Lateral
	if (CurrentValue.Y != 0)
	{
		AddMovementInput(GetActorRightVector(), CurrentValue.Y); // * CurrentMoveSpeed); // * GetWorld()->GetDeltaSeconds());
	}

	// Vertical
	if (CurrentValue.Z != 0)
	{
		AddMovementInput(GetActorUpVector(), CurrentValue.Z); // * CurrentMoveSpeed * GetWorld()->GetDeltaSeconds());
	}
}

void ACharacterBase::Look(const FInputActionValue& Value)
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

void ACharacterBase::PrimaryTappedAction(const FInputActionValue& Value)
{
}

void ACharacterBase::PrimaryHeldAction(const FInputActionValue& Value)
{
}

void ACharacterBase::SecondaryTappedAction(const FInputActionValue& Value)
{
	// ----- Return to Keeper Character
	AKeeperPlayerController* KeeperPlayerController = Cast<AKeeperPlayerController>(GetController());
	KeeperPlayerController->ReturnToKeeperCharacter();
}

void ACharacterBase::SecondaryHeldAction(const FInputActionValue& Value)
{
}

void ACharacterBase::ModifyMoveSpeed(const FInputActionValue& Value)
{
}


