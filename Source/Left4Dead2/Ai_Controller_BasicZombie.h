// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Ai_Controller_BasicZombie.generated.h"
//±Ë¿Ø≥≠πŸ∫∏
/**
 * 
 */
UCLASS()
class LEFT4DEAD2_API AAi_Controller_BasicZombie : public AAIController
{
	GENERATED_BODY()
	

public:

	AAi_Controller_BasicZombie();

	virtual void OnPossess(APawn* InPawn) override;

	static const FName Key_HasLineOfSight;
	static const FName Key_EnemyActor;
	static const FName Key_PatrolLocation;



	void RunAI();
	void StopAI();

protected:

	UPROPERTY()
	UBlackboardComponent* BlackboardComp = Blackboard;

private:

	UPROPERTY()
	class UBehaviorTree* BTAsset;

	UPROPERTY()
	class UBlackboardData* BBAsset;


};
