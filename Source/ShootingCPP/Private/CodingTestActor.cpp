// Fill out your copyright notice in the Description page of Project Settings.

#include "CodingTestActor.h"
// #include "ShootingCPP/Public/CodingTestActor.h" <- 이것도 불필요합니다. 이미 위에서 포함됨.
// #include "Runtime/Solaris/uLangCore/Public/uLang/Common/Common.h" <- 이 줄을 반드시 삭제하세요!

// Sets default values
ACodingTestActor::ACodingTestActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACodingTestActor::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Hello World!"));

	// 변수명들이 Header(.h)에 선언되어 있다는 가정하에 출력
	UE_LOG(LogTemp, Warning, TEXT("%d"), number1);
	UE_LOG(LogTemp, Warning, TEXT("%.2f"), number2);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *name);
	UE_LOG(LogTemp, Warning, TEXT("%d"), isReady);
	UE_LOG(LogTemp, Warning, TEXT("Add 결과: %d"), AddCustom(number3, number4));

	// 조건문
	if (number3 > 50)
	{
		UE_LOG(LogTemp, Warning, TEXT("number3은 50보다 큽니다."));
	}
	else if (number3 == 50)
	{
		UE_LOG(LogTemp, Warning, TEXT("number3는 50입니다."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("number3는 50보다 작습니다."));
	}

	// 반복문
	for (int32 i = 1; i <= 5; i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("반복횟수 : %d"), i);
	}
}

int32 ACodingTestActor::AddCustom(int32 a, int32 b)
{
	return a + b;
}

// Called every frame
void ACodingTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
