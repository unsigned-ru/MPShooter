// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HeroProjectile.h"
#include "UnrealNetwork.h"

// Sets default values
AHeroCharacter::AHeroCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	FP_Camera = CreateDefaultSubobject<UCameraComponent>(FName("FP_Camera"));
	FP_Camera->SetupAttachment(GetCapsuleComponent());
	FP_Camera->bUsePawnControlRotation = true;

	FP_CharacterMesh = CreateDefaultSubobject<USkeletalMeshComponent>(FName("FP_Mesh"));
	FP_CharacterMesh->SetupAttachment(FP_Camera);
	FP_CharacterMesh->CastShadow = false;
	FP_CharacterMesh->bCastDynamicShadow = false;
	FP_CharacterMesh->SetOnlyOwnerSee(true);

	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(FName("FP_Gun"));
	FP_Gun->SetupAttachment(FP_CharacterMesh);
	FP_Gun->CastShadow = false;
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->SetOnlyOwnerSee(true);
	FP_Gun->AttachTo(FP_CharacterMesh, FName("WeaponSocket"));

	CurrentAmmo = MaxAmmo;
}

// Called when the game starts or when spawned
void AHeroCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AHeroCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AHeroCharacter::MoveForward(float Rate)
{
	GetMovementComponent()->AddInputVector(GetActorForwardVector() * Rate);
}

void AHeroCharacter::MoveRight(float Rate)
{
	GetMovementComponent()->AddInputVector(GetActorRightVector() * Rate);
}

void AHeroCharacter::LookUp(float Amount)
{
	AddControllerPitchInput(Amount);
}

void AHeroCharacter::LookRight(float Amount)
{
	AddControllerYawInput(Amount);
}


bool AHeroCharacter::ServerRPCPrimaryFire_Validate() { return true; }
void AHeroCharacter::ServerRPCPrimaryFire_Implementation()
{
	FVector CameraLoc = FP_Camera->GetComponentLocation();
	FVector DirectionVector = GetControlRotation().Vector();
	DirectionVector.Normalize();

	GetWorld()->SpawnActor<AHeroProjectile>(ProjectileBP, CameraLoc + (DirectionVector * 65) , GetControlRotation());

	CurrentAmmo--;
}

bool AHeroCharacter::ServerRPCSecondaryFire_Validate() { return true; }
void AHeroCharacter::ServerRPCSecondaryFire_Implementation()
{
}

bool AHeroCharacter::ServerRPCTakeDamage_Validate(float amount) { return true; }
void AHeroCharacter::ServerRPCTakeDamage_Implementation(float Amount)
{
	Health -= Amount;
}


void AHeroCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(AHeroCharacter, Health);
	DOREPLIFETIME(AHeroCharacter, CurrentAmmo);
}