// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyActor.generated.h"

UCLASS()
class SHOOTINGCPP_API AEnemyActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// 박스 충돌체 컴포넌트
	UPROPERTY(EditAnywhere)
	class UBoxComponent* boxComp;
	
	// 스태틱 메시 컴포넌트
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* meshComp;
	
	// 이동 속도
	UPROPERTY(EditAnywhere)
	float movingSpeed = 600.f;
	
	// 플레이어 추적 확률(0~100%)
	UPROPERTY(EditAnywhere)
	int32 traceRate = 50;
	
	// 충돌 이벤트 함수 - OnComponentBeginOverlap 델리게이트에 등록할 함수
	UFUNCTION()
	void OnEnemyOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
						 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
						 const FHitResult& SweepResult);
	
private:
	FVector dir;
	
};
