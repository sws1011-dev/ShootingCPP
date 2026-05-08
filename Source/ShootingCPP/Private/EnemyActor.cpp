// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyActor.h"

#include "EngineUtils.h"
#include "PlayerPawn.h"
#include "ShootingGameModeBase.h"
#include "Components/BoxComponent.h"


// Sets default values
AEnemyActor::AEnemyActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 박스 콜리전 컴포넌트 생성
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("My Box Component"));

	// 생성한 박스 콜리전 컴포넌트를 최상단 컴포넌트로 설정
	SetRootComponent(boxComp);

	// 스태틱 매시 컴포넌트 생성
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Mesh Component"));

	// 박스 콜리전 자식으로 스태틱 매시 컴포넌트 설정
	meshComp->SetupAttachment(boxComp);

	// 박스 콜라이더 크기를 50x50x50 설정
	FVector boxSize = FVector(50.0f, 50.0f, 50.0f);
	boxComp->SetBoxExtent(boxSize);

	// 아래 처럼 에디터에서 생성할 프리셋 이름을 컴포넌트에 세팅해준다.
	boxComp->SetCollisionProfileName(TEXT("Enemy"));
}

// Called when the game starts or when spawned
void AEnemyActor::BeginPlay()
{
	Super::BeginPlay();

	// 1~100 사이 임의 값 추첨
	int drawResult = FMath::RandRange(1, 100);
	if (drawResult <= traceRate)
	{
		// 추적을 위한 액터 탐색 반복 TActorIterator 활용
		// for(TActorIterator<찾으려는 클래스> 위치 포인터 변수; 변수 이름; ++변수증감식) { 실행부 }
		// 월드 공간에 APlayerPawn 클래스로 된 액터를 검색
		for (TActorIterator<APlayerPawn> player(GetWorld()); player; ++player)
		{
			// 찾은 액터 이름이 BP_PlayerPawn이라면,
			if (player->GetName().Contains(TEXT("BP_PlayerPawn")))
			{
				// 찾은 플레이어 위치 - 에너미 자신위치 = dir 방향 변수에 할당(그 방향으로 가기 위해서)
				dir = player->GetActorLocation() - GetActorLocation();
				dir.Normalize();
			}
		}
	}
	else
	{
		// 직진
		dir = GetActorForwardVector();
	}

	// OnComponentBeginOverlap 델리게이트에 OnOverlap 함수를 등록
	// "Overlap" 발생하면 OnEnemyOverlap() 호출해 라고 엔진에 등록하는 설정
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemyActor::OnEnemyOverlap);
}

void AEnemyActor::OnEnemyOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                 const FHitResult& SweepResult)
{
	// 충돌한 상대 액터를 APlayerActor 클래스로 변환
	APlayerPawn* player = Cast<APlayerPawn>(OtherActor);
	if (player != nullptr)
	{
		// 충돌된 플레이어 제거
		OtherActor->Destroy();

		// 게임 오버 메뉴 ShowMenu() 함수 호출
		AShootingGameModeBase* currentGameModeBase = Cast<AShootingGameModeBase>(GetWorld()->GetAuthGameMode());
		if (currentGameModeBase != nullptr)
		{
			currentGameModeBase->ShowMenu();
		}
	}
	// 적 자신도 제거
	Destroy();
}

// Called every frame
void AEnemyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 적이 정해진 방향으로 이동
	FVector newLocation = GetActorLocation() + dir * movingSpeed * DeltaTime;
	SetActorLocation(newLocation);
}
