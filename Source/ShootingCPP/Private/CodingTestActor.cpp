// Fill out your copyright notice in the Description page of Project Settings.


#include "CodingTestActor.h"
#include "ShootingCPP/Public/CodingTestActor.h"

#include "Runtime/Solaris/uLangCore/Public/uLang/Common/Common.h"

// Sets default values
ACodingTestActor::ACodingTestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACodingTestActor::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Hello World!"));
	
	UE_LOG(LogTemp, Warning, TEXT("%d"), number1);
	UE_LOG(LogTemp, Warning, TEXT("%.2f"), number2);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *name);	
	UE_LOG(LogTemp, Warning, TEXT("%d"), isReady);	
	UE_LOG(LogTemp, Warning, TEXT("Add 결과: %d"), Add(number3, number4));
}

int32 ACodingTestActor::Add(int32 a, int32 b)
{
	int32 result = a + b;
	return result;
}

// Called every frame
void ACodingTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



