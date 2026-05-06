// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CodingTestActor.generated.h"

UCLASS()
class ACodingTestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACodingTestActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// 기본 자료형 변수
	UPROPERTY(EditAnywhere) // 블루프린트 설정창 OK / 레벨에 배치된 액터(인스턴스) OK
	int32 number1 = 10;
	
	UPROPERTY(VisibleAnywhere) // 값을 볼 수 있지만 수정 불가 -> 코드에서만 수정할 수 있고, 에디터에서는 참고용
	float number2 = 3.14f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite) // 블루프린트 이벤트그래프에서 읽기쓰기 모두 가능
	int32 number3 = 30;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly) // 블루프린트 이벤트그래프에서 읽기전용
	int32 number4 = 40;
	
	UPROPERTY(EditInstanceOnly) // 레벨에 배치된 액터 인스턴스에서만 수정 가능
	FString name = TEXT("홍길동");
	
	UPROPERTY(EditDefaultsOnly) // 블루프린트 설정에서만 수정 가능
	bool isReady = false;
	
	// 함수 사용
	int32 Add(int32 a, int32 b);
};
