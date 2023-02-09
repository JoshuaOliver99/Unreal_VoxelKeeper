// Fill out your copyright notice in the Description page of Project Settings.


#include "KeeperCharacter.h"

#include "CharacterBase.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AKeeperCharacter::AKeeperCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
		EnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &AKeeperCharacter::Move);
		EnhancedInputComponent->BindAction(LookInputAction, ETriggerEvent::Triggered, this, &AKeeperCharacter::Look);
		
		EnhancedInputComponent->BindAction(PrimaryTappedInputAction, ETriggerEvent::Triggered, this, &AKeeperCharacter::PrimaryTappedAction);
		EnhancedInputComponent->BindAction(PrimaryHeldInputAction, ETriggerEvent::Triggered, this, &AKeeperCharacter::PrimaryHeldAction);
		EnhancedInputComponent->BindAction(PrimaryHeldInputAction, ETriggerEvent::Completed, this, &AKeeperCharacter::PrimaryHeldAction);
		
		EnhancedInputComponent->BindAction(SecondayTappedInputAction, ETriggerEvent::Triggered, this, &AKeeperCharacter::SecondayTappedAction);
		EnhancedInputComponent->BindAction(SecondayHeldInputAction, ETriggerEvent::Triggered, this, &AKeeperCharacter::SecondayHeldAction);
		EnhancedInputComponent->BindAction(SecondayHeldInputAction, ETriggerEvent::Completed, this, &AKeeperCharacter::SecondayHeldAction);
	
		EnhancedInputComponent->BindAction(SpeedModifierInputAction, ETriggerEvent::Triggered, this, &AKeeperCharacter::ModifyMoveSpeed);
		EnhancedInputComponent->BindAction(SpeedModifierInputAction, ETriggerEvent::Completed, this, &AKeeperCharacter::ModifyMoveSpeed);
	}
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

	// ----- Init settings
	GetCharacterMovement()->MaxFlySpeed = BaseMoveSpeed;

	KeeperPlayerController = Cast<APlayerController>(GetController());
}




void AKeeperCharacter::Move(const FInputActionValue& Value)
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

void AKeeperCharacter::Look(const FInputActionValue& Value)
{
	if (bAllowRotation == false)
	{
		return;
	}
	
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

void AKeeperCharacter::PrimaryTappedAction(const FInputActionValue& Value)
{
	if (KeeperPlayerController == nullptr)
	{
		return;
	}
	
	FHitResult HitResult;
	KeeperPlayerController->GetHitResultUnderCursor(ECC_Camera, false, HitResult);

	// Debug
	DrawDebugSphere(GetWorld(), HitResult.Location, 10.f, 12, FColor::Green, false, 5.f);
	UE_LOG(LogTemp, Warning, TEXT("PrimaryTapped: %s"), *HitResult.GetActor()->GetActorNameOrLabel());

	// TODO:
	// Possess a minion
	ACharacterBase* CharacterBase = Cast<ACharacterBase>(HitResult.GetComponent()->GetOwner());
	if (CharacterBase)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACharacterBase Found!.. %s"), *HitResult.GetActor()->GetActorNameOrLabel());

		// Possess
		// Source: http://jollymonsterstudio.com/2019/09/05/unreal-engine-c-fundamentals-character-possession-and-changing-materials/
		
		// save a copy of our controller
		AController* SavedController = GetController();
		// unpossess first ( helps with multiplayer )
		SavedController->UnPossess();
		// disable movement mode
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
		// possess our new actor
		SavedController->Possess(Cast<APawn>(CharacterBase));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ACharacterBase NOT found: %s"), *HitResult.GetActor()->GetActorNameOrLabel());

	}
	
	
	// TODO:
	// Grab a minion
	// Tag a Tile
}

void AKeeperCharacter::PrimaryHeldAction(const FInputActionValue& Value)
{
	if (KeeperPlayerController == nullptr)
	{
		return;
	}

	FHitResult HitResult;
	KeeperPlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
	
	if (Value.Get<bool>())
	{
		DrawDebugSphere(GetWorld(), HitResult.Location, 15.f, 12, FColor::White, false, 5.f);

		// TODO:
		// Tagging or Untagging terrain
		// Rapid Building or Selling
		// Spell Charging
	}
	else
	{
		DrawDebugSphere(GetWorld(), HitResult.Location, 15.f, 12, FColor::Black, false, 5.f);

		// TODO:
		// Complete ongoing action
	}
}


void AKeeperCharacter::SecondayTappedAction(const FInputActionValue& Value)
{
	// TODO:
	// Implement Slap
	// Drop a grabbed minion
}
void AKeeperCharacter::SecondayHeldAction(const FInputActionValue& Value)
{
	bAllowRotation = Value.Get<bool>();
}


void AKeeperCharacter::ModifyMoveSpeed(const FInputActionValue& Value)
{
	if (Value.Get<bool>())
	{
		GetCharacterMovement()->MaxFlySpeed = BoostedMoveSpeed;
	}
	else
	{
		GetCharacterMovement()->MaxFlySpeed = BaseMoveSpeed;
	}
}
