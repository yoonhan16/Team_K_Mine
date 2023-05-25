// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BP_Basic_Zombie.generated.h"


class UStaticMeshComponent;
class UBoxComponent;


UCLASS()
class LEFT4DEAD2_API ABP_Basic_Zombie : public ACharacter
{
	GENERATED_BODY()

public:

	// Sets default values for this character's properties
	ABP_Basic_Zombie();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty > & OutLifetimeProps) const override;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Variable")
	float MaxHP = 15.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Variable")
	float CurHP = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Variable")
	bool HasOverlapped = false;

	UPROPERTY(EditAnywhere, BlueprintReadwrite, Replicated, Category = "Variable")
	float Timer = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadwrite, Replicated, Category = "Variable")
	float AttackTimer = 0.0f;
	 
	UPROPERTY(EditAnywhere, BlueprintReadwrite, Replicated, Category = "Variable")
	bool StartCount = false;

	UPROPERTY(EditAnywhere, BlueprintReadwrite, Replicated, Category = "Variable")
	bool flag = false;

	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void CheckHP(bool Check);



	UFUNCTION(BlueprintCallable, Category = "Function")
	void UpdateSpeed(UPARAM(DisplayName="Speed") float Speed);

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);





private:
	



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* Body;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* LeftArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* RightArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* Leg;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UBoxComponent* Box;


};
