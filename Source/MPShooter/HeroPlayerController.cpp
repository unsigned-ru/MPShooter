// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroPlayerController.h"
#include "HeroCharacter.h"

AHeroPlayerController::AHeroPlayerController()
{

}

void AHeroPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ControlledCharacter = Cast<AHeroCharacter>(GetPawn());
}

void AHeroPlayerController::RequestMoveRight(float Rate)
{
	if (!ControlledCharacter) { return; } //TODO: Add conditions here
	
	ControlledCharacter->MoveRight(Rate);
}

void AHeroPlayerController::RequestMoveForward(float Rate)
{
	if (!ControlledCharacter) { return; } //TODO: Add conditions here
	
	ControlledCharacter->MoveForward(Rate);
}

void AHeroPlayerController::RequestJump()
{
	if (!ControlledCharacter) { return; } //TODO: Add conditions here

	ControlledCharacter->Jump();
}

void AHeroPlayerController::RequestLookRight(float Rate)
{
	if (!ControlledCharacter) { return; } //TODO: Add conditions here
	ControlledCharacter->LookRight(Rate * Sensitivity);
}

void AHeroPlayerController::RequestLookUp(float Rate)
{
	if (!ControlledCharacter) { return; } //TODO: Add conditions here

	ControlledCharacter->LookUp(Rate * Sensitivity);
}

void AHeroPlayerController::RequestPrimaryFire()
{
	if (!ControlledCharacter) { return; } //TODO: Add conditions here
	
	ControlledCharacter->ServerRPCPrimaryFire();
}

void AHeroPlayerController::RequestSecondaryFire()
{
	if (!ControlledCharacter) { return; } //TODO: Add conditions here
}

void AHeroPlayerController::RequestTakeDamage(float Amount)
{
	if (!ControlledCharacter || Amount == 0) { return; } //TODO: Add conditions here
	if (Amount > ControlledCharacter->GetHealth()) { /*TODO: Die and respawn.*/}
	else { ControlledCharacter->ServerRPCTakeDamage(Amount); }
}
