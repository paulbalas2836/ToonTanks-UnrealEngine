// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PawnTank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	APawn* PlayerTank = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	MoveToActor(PlayerTank);
	if (AIBehavior != nullptr)
	{
		RunBehaviorTree(AIBehavior);

		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
		GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerTank->GetActorLocation());
	}

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* PlayerTank = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	MoveToActor(PlayerTank);
}
