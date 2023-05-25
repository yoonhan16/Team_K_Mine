// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BP_Basic_Zombie.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_ChaseBasic.generated.h"

/**
 * 
 */
UCLASS()
class LEFT4DEAD2_API UBTTask_ChaseBasic : public UBTTaskNode
{
	GENERATED_BODY()
	
public:

	UBTTask_ChaseBasic();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Variable")
	float ChaseSpeed = 700.0f;

};
