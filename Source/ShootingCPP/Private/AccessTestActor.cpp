// Fill out your copyright notice in the Description page of Project Settings.


#include "AccessTestActor.h"

#include "CodingTestActor.h"


// Sets default values
AAccessTestActor::AAccessTestActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAccessTestActor::BeginPlay()
{
	Super::BeginPlay();
	
	ACodingTestActor* testActor = NewObject<ACodingTestActor>(this);
	testActor->number1 = -100;
	UE_LOG(LogTemp, Warning, TEXT("Number1: %i"), testActor->number1);
	
}

// Called every frame
void AAccessTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

