// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KillZone.generated.h"

UCLASS()
class SHOOTINGCPP_API AKillZone : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AKillZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// 박스 콜리전 컴포넌트 선언
	UPROPERTY(EditAnywhere)
	class UBoxComponent* boxComp;

	// 충돌 이벤트 함수 - OnComponentBeginOverlap 델리게이트에 등록할 함수
	UFUNCTION()
	void OnKillZoneOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                       UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                       const FHitResult& SweepResult);
};
