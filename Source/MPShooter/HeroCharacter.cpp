// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AHeroCharacter::AHeroCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	FP_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("FP_Camera"));
	FP_Camera->SetupAttachment(GetCapsuleComponent());
	FP_Camera->bUsePawnControlRotation = true;

	FP_CharacterMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Mesh"));
	FP_CharacterMesh->SetupAttachment(FP_Camera);
	FP_CharacterMesh->CastShadow = false;
	FP_CharacterMesh->bCastDynamicShadow = false;
	FP_CharacterMesh->SetOnlyOwnerSee(true);


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
