// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HeroProjectile.generated.h"

UCLASS()
class MPSHOOTER_API AHeroProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHeroProjectile();

	UPROPERTY(VisibleDefaultsOnly)
		class UProjectileMovementComponent* ProjectileMovement;
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Mesh;
	UPROPERTY(BlueprintReadOnly)
		float ProjectileDamage = 10.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
