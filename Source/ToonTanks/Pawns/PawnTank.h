// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTank.generated.h"

/**
 * 
 */
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class TOONTANKS_API APawnTank : public APawnBase
{
	GENERATED_BODY()
public:
	APawnTank();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void HandleDestruction() override;
	bool GetIsPlayerAlive();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Speed")
		float MovementSpeed = 100.f;

	UPROPERTY(EditAnywhere, Category = "Speed")
		float TurnSpeed = 100.f;

	APlayerController* PlayerControllerRef;
	FVector MoveDirection;
	FQuat RotationDirection;
	bool bIsPlayerAlive = true;

	void CalculateMoveInput(float Value);
	void CalculateRotateInput(float Value);

	void Move();
	void Rotate();
};
