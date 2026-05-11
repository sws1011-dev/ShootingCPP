// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"

#include "Bullet.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
APlayerPawn::APlayerPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// // 박스 콜리전 컴포넌트 생성
	// boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("My Box Component"));
	//
	// // 생성한 박스 콜리전 컴포넌트를 최상단 컴포넌트로 설정
	// SetRootComponent(boxComp);

	// 스태틱 매시 컴포넌트 생성
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Mesh Component"));

	// 박스 콜리전 자식으로 스태틱 매시 컴포넌트 설정
	SetRootComponent(meshComp);

	// // 박스 콜라이더 크기를 50x50x50 설정
	// FVector boxSize = FVector(50.0f, 50.0f, 50.0f);
	// boxComp->SetBoxExtent(boxSize);

	// 총구 컴포넌트 설정
	firePosition = CreateDefaultSubobject<UArrowComponent>(TEXT("Fire Component"));
	firePosition->SetupAttachment(meshComp);

	// 충돌 채널 설정을 C++에서 직접 하는 경우
	// 충돌 설정은 채널/응답 조합이 복잡해질 가능성이 높기때문에, 언리얼 에디터의 프리셋으로 관리하는 것이 유리함(관례적)
	// boxComp->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);	// Player
	// boxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	// boxComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	// boxComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Ignore);
	// 아래 처럼 에디터에서 생성할 프리셋 이름을 컴포넌트에 세팅해준다.
	meshComp->SetCollisionProfileName(TEXT("Player"));
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* pc = GetWorld()->GetFirstPlayerController();
	if (pc != nullptr)
	{
		// 플레이어 컨트롤러로부터 입력 서브시스템 정보 가져오기
		UEnhancedInputLocalPlayerSubsystem* subsys =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer());

		if (subsys != nullptr)
		{
			subsys->AddMappingContext(imcPlayerInput, 0);
		}
	}
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Tick 당, 매프레임 마다 호출됨
	// 사용자 입력 키를 이용해서
	FVector dir = FVector(0, h, v);
	dir.Normalize(); // 방향 벡터 길이가 1이 되도록 정규화(1로 제한)
	// y축(좌우) / z축(상하)을 분리하여 이동될 수 있도록 수정
	// 한축이 막혀도, 다른 축은 계속 이동할 수 있도록 처리하기 위해 분리
	FVector vector = dir * moveSpeed * DeltaTime;
	SetActorLocation(GetActorLocation() + FVector(0, vector.Y, 0), true);
	SetActorLocation(GetActorLocation() + FVector(0, 0, vector.Z), true);
}

// 사용자가 키를 누를 때 실행되며 h,v 변수를 재할당하는 함수
void APlayerPawn::OnInputHorizontal(const struct FInputActionValue& value)
{
	h = value.Get<float>();
}

void APlayerPawn::OnInputVertical(const struct FInputActionValue& value)
{
	v = value.Get<float>();
}

void APlayerPawn::Fire()
{
	// SpawnActor<T>() 함수 구성
	// SpawnActor<생성하려는 액터 클래스>(파일 변수, 생성할 위치, 생성할 방향회전값)
	ABullet* bullet = GetWorld()->SpawnActor<ABullet>(bulletFactory,
	                                                  firePosition->GetComponentLocation(),
	                                                  firePosition->GetComponentRotation());

	UGameplayStatics::PlaySound2D(GetWorld(), fireSound);
}


// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* eic = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (eic != nullptr)
	{
		// BindAction() 함수 구성
		// BindAction(IA이름, 입력이벤트타입, 연결할 함수가 있는 클래스, 연결할 함수의 주소값)
		eic->BindAction(iaHorizontal, ETriggerEvent::Triggered, this, &APlayerPawn::OnInputHorizontal);
		eic->BindAction(iaHorizontal, ETriggerEvent::Completed, this, &APlayerPawn::OnInputHorizontal);
		eic->BindAction(iaVertical, ETriggerEvent::Triggered, this, &APlayerPawn::OnInputVertical);
		eic->BindAction(iaVertical, ETriggerEvent::Completed, this, &APlayerPawn::OnInputVertical);
		eic->BindAction(iaFire, ETriggerEvent::Started, this, &APlayerPawn::Fire);
	}
}
