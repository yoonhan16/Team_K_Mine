// Fill out your copyright notice in the Description page of Project Settings.


#include "Ai_Controller_BasicZombie.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"

const FName AAi_Controller_BasicZombie::Key_HasLineOfSight(TEXT("HasLineOfSight"));
const FName AAi_Controller_BasicZombie::Key_EnemyActor(TEXT("EnemyActor"));
const FName AAi_Controller_BasicZombie::Key_PatrolLocation(TEXT("PatrolLocation"));


AAi_Controller_BasicZombie::AAi_Controller_BasicZombie()
{


	static ConstructorHelpers::FObjectFinder<UBlackboardData>BBObject(TEXT("BlackboardData'/Game/TEAM_K/Left4Dead/KIM_YoonHan/BlackBoard/BB_BasicZombie.BB_BasicZombie'"));
	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree>BTObject(TEXT("BehaviorTree'/Game/TEAM_K/Left4Dead/KIM_YoonHan/Behaviour_Tree/BT_BasicZombie.BT_BasicZombie'"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}


}

void AAi_Controller_BasicZombie::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	RunAI();

}

void AAi_Controller_BasicZombie::RunAI()
{
	if (UseBlackboard(BBAsset, BlackboardComp))
	{
		RunBehaviorTree(BTAsset);
	}
}

void AAi_Controller_BasicZombie::StopAI()
{
	UBehaviorTreeComponent* BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (nullptr == BehaviorTreeComponent) return;

	BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
}
