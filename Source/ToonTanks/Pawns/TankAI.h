// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnTank.h"
#include "TankAI.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATankAI : public APawnBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void HandleDestruction() override;

private:
	float ReturnDistanceToPlayer();
	void FireAI();
	void MoveTo(float DeltaTime);
	void ReturnLocation(float DeltaTime);
	void RotateToMove(float DeltaTime);
	void RotateToReturn(float DeltaTime);
	void RotateToPlayer(float DeltaTime);
	void MoveToPlayer(float DeltaTime);

	APawnTank* PlayerTank;
	FTimerHandle FireRateTimerHandle;
	ATankAI* OtherTank;

	UPROPERTY(EditAnywhere, Category = "Combat")
		float FireRange = 500.f;
	UPROPERTY(EditAnywhere, Category = "Combat")
		float FireRate = 1.f;

	//Movement
	float TankLastMove = 0.f;
	float TankLastReturn = 0.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
		float TargetY = -1600.f;
	UPROPERTY(EditAnywhere, Category = "Movement")
		float MovementSpeed =1.5;
	UPROPERTY(EditAnywhere, Category = "Movement")
		float ReturnY = -750.f;
	UPROPERTY(EditAnywhere, Category = "Movement")
		float TankReturnDelay = 2.f;
	UPROPERTY(EditAnywhere, Category = "Movement")
		float TankMoveDelay = 2.f;
	UPROPERTY(EditAnywhere, Category = "Movement")
		float FollowRange = 600.f;
	UPROPERTY(EditAnywhere, Category = "Movement")
		bool CanPatrol = true;

	float CurrentY;
	float CurrentX;
	float InitialX;
	float InitialY;
	bool CheckMovement;
	bool PlayerSaw;

	//Rotation
	UPROPERTY(EditAnywhere, Category = "Rotation")
		float TargetYaw = 180.f;
	UPROPERTY(EditAnywhere, Category = "Rotation")
		float RotationSpeed = 2.f;

	float CurrentYaw;
	float InitialYaw;
};
