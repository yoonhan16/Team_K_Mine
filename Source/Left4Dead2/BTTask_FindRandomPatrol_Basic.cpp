// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindRandomPatrol_Basic.h"
#include "Ai_Controller_BasicZombie.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"


//return EBTNodeResult::Type();

UBTTask_FindRandomPatrol_Basic::UBTTask_FindRandomPatrol_Basic()
{
	NodeName = TEXT("FindRandomPatrol_Basic");
}

EBTNodeResult::Type UBTTask_FindRandomPatrol_Basic::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{


	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
	{
		return EBTNodeResult::Failed;
	}

	ABP_Basic_Zombie* Basic_Zombie = Cast<ABP_Basic_Zombie>(ControllingPawn);

	if (Basic_Zombie)
	{
		Basic_Zombie->UpdateSpeed(PatrolSpeed);
	}

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());
	if (nullptr == NavSystem)
	{
		return EBTNodeResult::Failed;
	}

	FVector Origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector(AAi_Controller_BasicZombie::Key_PatrolLocation);
	FNavLocation NextPatrol;
	if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 2000.0f, NextPatrol))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(AAi_Controller_BasicZombie::Key_PatrolLocation, NextPatrol.Location);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
