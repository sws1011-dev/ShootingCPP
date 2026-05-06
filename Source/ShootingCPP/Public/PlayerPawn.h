// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

UCLASS()
class SHOOTINGCPP_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 박스 충돌체 컴포넌트
	UPROPERTY(EditAnywhere)
	class UBoxComponent* boxComp;

	// 스태틱 메시 컴포넌트
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* meshComp;

	// IMC 파일의 포인터 변수
	UPROPERTY(EditAnywhere)
	class UInputMappingContext* imcPlayerInput;

	// IA 파일의 포인터 변수
	UPROPERTY(EditAnywhere)
	class UInputAction* iaHorizontal;

	UPROPERTY(EditAnywhere)
	class UInputAction* iaVertical;
	
	// 이동 속도 변수
	UPROPERTY(EditAnywhere)
	float moveSpeed = 500.f;

private:
	// 사용자 키 입력값을 받을 변수
	float h;
	float v;
	
	// 입력 이벤트 발동 시 실행 할 함수
	void OnInputHorizontal(const struct FInputActionValue& value);
	void OnInputVertical(const struct FInputActionValue& value);
	
};
