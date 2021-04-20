// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAI.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"
#include "Kismet/KismetMathLibrary.h"


void ATankAI::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &ATankAI::FireAI, FireRate, true);
	PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
	
	//Setting up the Location
	InitialY = GetActorLocation().Y;
	CurrentY = InitialY;
	TargetY += InitialY;
	InitialX = GetActorLocation().X;
	CurrentX = InitialX;
	CheckMovement = true;
	PlayerSaw = true;

	//Setting up the Rotation
	InitialYaw = GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	TargetYaw += InitialYaw;
}

void ATankAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!PlayerTank)
	{
		return;
	}
	if (ReturnDistanceToPlayer() <= FollowRange && (GetActorLocation().Y >= PlayerTank->GetActorLocation().Y + 50 || GetActorLocation().Y <= PlayerTank->GetActorLocation().Y - 50) && (GetActorLocation().X >= PlayerTank->GetActorLocation().X + 50 || GetActorLocation().X <= PlayerTank->GetActorLocation().X - 50))
	{
		RotateToPlayer(DeltaTime);
		MoveToPlayer(DeltaTime);
		CanPatrol = false;
	}
     else
	{  
		if (!CanPatrol)
		{
			return;
		}

		if (CheckMovement && PlayerSaw)
		{
			RotateToReturn(DeltaTime);
			if (GetWorld()->GetTimeSeconds() - TankLastReturn >= TankReturnDelay)
			{
				MoveTo(DeltaTime);
				TankLastMove = GetWorld()->GetTimeSeconds();
			}
		}
		else
		{
			RotateToMove(DeltaTime);
			if (GetWorld()->GetTimeSeconds() - TankLastMove >= TankMoveDelay)
			{
				ReturnLocation(DeltaTime);
				TankLastReturn = GetWorld()->GetTimeSeconds();
			}
		}
	}

	if (ReturnDistanceToPlayer() > FireRange)
	{
		return;
	}
	RotateTurret(PlayerTank->GetActorLocation());
}

float ATankAI::ReturnDistanceToPlayer()
{
	if (!PlayerTank)
	{
		return 0.f;
	}
	return FVector::Dist(PlayerTank->GetActorLocation(), GetActorLocation());
}

void ATankAI::FireAI()
{
	if (!PlayerTank || !PlayerTank->GetIsPlayerAlive())
	{
		return;
	}
	if (ReturnDistanceToPlayer() <= FireRange)
	{
		Fire();
	}
}

void ATankAI::MoveTo(float DeltaTime)
{
	CurrentY = FMath::Lerp(CurrentY, TargetY, DeltaTime * MovementSpeed);
	FVector TargetLocation = GetActorLocation();
	TargetLocation.Y = CurrentY;

	if (TargetLocation.Y <= ReturnY) {
		CheckMovement = false;
	}
	SetActorLocation(TargetLocation);
}

void ATankAI::ReturnLocation(float DeltaTime)
{
	CurrentY = FMath::Lerp(CurrentY, InitialY, DeltaTime * MovementSpeed);
	FVector TargetLocation = GetActorLocation();
	TargetLocation.Y = CurrentY;

	if(CurrentY >= InitialY - 50.f)
	{	
		CheckMovement = true;
	}

	SetActorLocation(TargetLocation);
}

void ATankAI::RotateToMove(float DeltaTime)
{
	CurrentYaw = FMath::Lerp(CurrentYaw, TargetYaw, DeltaTime * RotationSpeed);
	FRotator TargetRotation = GetActorRotation();
	TargetRotation.Yaw = CurrentYaw;

	SetActorRotation(TargetRotation);
}

void ATankAI::RotateToReturn(float DeltaTime)
{
	CurrentYaw = FMath::Lerp(CurrentYaw, InitialYaw, DeltaTime * RotationSpeed);
	FRotator TargetRotation = GetActorRotation();
	TargetRotation.Yaw = CurrentYaw;

	SetActorRotation(TargetRotation);
}

void ATankAI::RotateToPlayer(float DeltaTime)
{
	FRotator RotateTowardsPlayer = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), PlayerTank->GetActorLocation());
	FRotator AIRotation = FMath::RInterpTo(GetActorRotation(), RotateTowardsPlayer, DeltaTime, 1);
	SetActorRotation(AIRotation);
}

void ATankAI::MoveToPlayer(float DeltaTime)
{

	if (GetActorLocation().Y > PlayerTank->GetActorLocation().Y)
	{
		FVector Location = GetActorLocation();
		CurrentY = CurrentY - 7;
		Location.Y = CurrentY;
		SetActorLocation(Location);
	}
	else
	{
		FVector Location = GetActorLocation();
		CurrentY = CurrentY + 7;
		Location.Y = CurrentY;
		SetActorLocation(Location);
	}

	if (GetActorLocation().X > PlayerTank->GetActorLocation().X)
	{
		FVector Location = GetActorLocation();
		CurrentX = CurrentX - 7;
		Location.X = CurrentX;
		SetActorLocation(Location);
	}
	else
	{
		FVector Location = GetActorLocation();
		CurrentX = CurrentX + 7;
		Location.X = CurrentX;
		SetActorLocation(Location);
	}
	/*
	PlayerTank->GetActorForwardVector();
	CurrentY = FMath::Lerp(CurrentY, PlayerTank->GetActorLocation().Y, DeltaTime * MovementSpeed);
	CurrentX = FMath::Lerp(CurrentX, PlayerTank->GetActorLocation().X, DeltaTime * MovementSpeed);
	FVector MoveTowardsPlayer = GetActorLocation();
	MoveTowardsPlayer.X = CurrentX;
	MoveTowardsPlayer.Y = CurrentY;
	SetActorLocation(MoveTowardsPlayer);*/
}

void ATankAI::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}