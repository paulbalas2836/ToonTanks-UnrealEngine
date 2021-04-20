// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraShake.h"
#include "ProjectileBase.generated.h"

class UProjectileMovementComponent;
UCLASS()
class TOONTANKS_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UProjectileMovementComponent* ProjectileMovement;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* ProjectileMesh;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UParticleSystemComponent* ParticleTrail;

	UPROPERTY(EditDefaultsOnly , Category = "Damage")
	TSubclassOf<UDamageType> DamageType;
	UPROPERTY(EditAnywhere, Category = "Move")
	float MovementSpeed = 1300;
	UPROPERTY(EditAnywhere, Category = "Damage")
	float Damage = 25.f;

	UPROPERTY(EditAnywhere, Category = "Effect")
	UParticleSystem* HitParticle;
	UPROPERTY(EditAnywhere, Category = "Effect")
	USoundBase* HitSound;
	UPROPERTY(EditAnywhere, Category = "Effect")
	USoundBase* LaunchSound;

	UPROPERTY(EditAnywhere, Category = "Effects")
	TSubclassOf<UMatineeCameraShake> HitShake;

	 UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};
