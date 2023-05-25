// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_Basic_Zombie.h"
#include "Ai_Controller_BasicZombie.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Net/UnrealNetwork.h>
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Public/TimerManager.h"

void ABP_Basic_Zombie::GetLifetimeReplicatedProps(TArray<FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}


// Sets default values
ABP_Basic_Zombie::ABP_Basic_Zombie()
{

	AIControllerClass = AAi_Controller_BasicZombie::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BODY"));
	//RootComponent = USkeletalMeshComponent::SkeletalMeshComponent;
	Body->SetupAttachment(GetMesh());

	LeftArm = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftArm"));
	LeftArm->SetupAttachment(Body);
	LeftArm->AddLocalOffset(FVector(80.0f, 60.0f, 10.0f));

	RightArm = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightArm"));
	RightArm->SetupAttachment(Body);
	RightArm->AddLocalOffset(FVector(80.0f, -60.0f, 10.0f));

	Leg = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Leg"));
	Leg->SetupAttachment(Body);
	Leg->AddLocalOffset(FVector(-0.0f, 0.0f, -55.0f));

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackBox"));
	Box->SetupAttachment(Body);
	Box->AddLocalOffset(FVector(168.8f, -0.0f, 10.4f));
	Box->OnComponentBeginOverlap.AddDynamic(this, &ABP_Basic_Zombie::OnOverlapBegin);
	Box->OnComponentEndOverlap.AddDynamic(this, &ABP_Basic_Zombie::OnOverlapEnd);
}


void ABP_Basic_Zombie::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		HasOverlapped = true;

		if (ActorHasTag("Player") && AttackTimer == 1)
		{
			UGameplayStatics::ApplyDamage(OtherActor, 2.0f, GetController(), nullptr, NULL);
		}

	}
}

void ABP_Basic_Zombie::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		HasOverlapped = false;
	}
}


// Called when the game starts or when spawned
void ABP_Basic_Zombie::BeginPlay()
{
	Super::BeginPlay();

}

float ABP_Basic_Zombie::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	//UE_LOG(LogTemp, Warning, TEXT("ABP_Basic_Zombie::TakeDamage : Called"));

	if(UGameplayStatics::GetPlayerController(EventInstigator, 0))
	{
		CurHP = CurHP - Damage;

		UE_LOG(LogTemp, Warning, TEXT("CurHP = CurHP - Damage : Called"));
	}
	
	if (CurHP <= 0.0f && flag == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("CurHP = 0.0, flag == true : Called"));
		StartCount = true;
		flag = true;

		Body->SetSimulatePhysics(true);
		GetCharacterMovement()->StopMovementImmediately();
		GetCharacterMovement()->StopActiveMovement();

	}


	return 0.0f;
}

// Called every frame
void ABP_Basic_Zombie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (StartCount == true)
	{
		Timer = Timer + DeltaTime;

		if (Timer >= 2)
		{
			Destroy(false, true);
			StartCount = false;
			Timer = 0;
		}
	}

	if (HasOverlapped == true)
	{
		AttackTimer = AttackTimer + DeltaTime;

		if (AttackTimer >= 1)
		{
			AttackTimer = 0;
		}
	}

}

// Called to bind functionality to input
void ABP_Basic_Zombie::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool ABP_Basic_Zombie::CheckHP_Validate(bool Check)
{
	Check = StartCount;
	if (Check == true)
	{
		return true;
	}
	return false;
}

void ABP_Basic_Zombie::CheckHP_Implementation(bool Check)
{
	Check = StartCount;
	if (Check == true && flag == false)
	{
		flag = true;
		Body->SetSimulatePhysics(true);
		GetCharacterMovement()->StopMovementImmediately();
		GetCharacterMovement()->StopActiveMovement();
	}
}

void ABP_Basic_Zombie::UpdateSpeed(float Speed)
{
	GetCharacterMovement()->MaxWalkSpeed = Speed;
}
