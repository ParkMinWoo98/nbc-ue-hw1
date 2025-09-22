#include "BlinkPlatform.h"

// Sets default values
ABlinkPlatform::ABlinkPlatform()
	: bShow(true)
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(SceneRoot);

	PrimaryActorTick.bCanEverTick = true;
}

void ABlinkPlatform::BeginPlay()
{
	Super::BeginPlay();

	ShowPlatform(true, false);
	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle,
		this,
		&ABlinkPlatform::SwitchBlink,
		FMath::RandRange(0.0f, MaxInitialDelay),
		false);
}

void ABlinkPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABlinkPlatform::ShowPlatform(bool bSShow, bool bSetTimer)
{
	this->bShow = bSShow;
	StaticMesh->SetVisibility(bShow);
	if (bSetTimer)
	{
		GetWorld()->GetTimerManager().SetTimer(
			TimerHandle,
			this,
			&ABlinkPlatform::SwitchBlink,
			bShow ? DurationShow : DurationHide,
			false);
	}
}

void ABlinkPlatform::SwitchBlink()
{
	ShowPlatform(!bShow);
}
