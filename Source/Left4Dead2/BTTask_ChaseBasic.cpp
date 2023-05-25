// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ChaseBasic.h"
#include "Ai_Controller_BasicZombie.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

//return EBTNodeResult::Type();

UBTTask_ChaseBasic::UBTTask_ChaseBasic()
{
	NodeName = TEXT("ChaseBasic");
}

EBTNodeResult::Type UBTTask_ChaseBasic::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
	{
		return EBTNodeResult::Failed;
	}
	 
	ABP_Basic_Zombie* Basic_Zombie = Cast<ABP_Basic_Zombie>(ControllingPawn);

	if (Basic_Zombie)
	{
		Basic_Zombie->UpdateSpeed(ChaseSpeed);
	}

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());
	if (nullptr == NavSystem)
	{
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Succeeded;




}
