// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class SHOOTINGCPP_API ABullet : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 충돌체 콜리전 박스 포인터 변수 선언
	UPROPERTY(EditAnywhere)
	class UBoxComponent* boxComp;

	// 충돌체 메시 포인터 변수 선언
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* meshComp;

	// 총알 이동 속도 변수 선언
	UPROPERTY(EditAnywhere)
	float moveSpeed = 800.f;
	
	// 폭발 파티클 이펙트
	UPROPERTY(EditAnywhere)
	class UParticleSystem* explosionFX;

	// 충돌 이벤트 함수 - OnComponentBeginOverlap 델리게이트에 등록할 함수
	UFUNCTION()
	void OnBulletOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                     UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                     const FHitResult& SweepResult);
};
