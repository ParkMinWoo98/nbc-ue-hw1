#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
	: DirObserve(true)
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(SceneRoot);

	PrimaryActorTick.bCanEverTick = true;
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();
	if (StartRandomInRange)
	{
		FVector MinLocation = StartLocation + GetNormalizedWorldDir() * MinRange;
		FVector MaxLocation = StartLocation + GetNormalizedWorldDir() * MaxRange;
		FVector RandomLocation = FVector(
			FMath::RandRange(MinLocation.X, MaxLocation.X),
			FMath::RandRange(MinLocation.Y, MaxLocation.Y),
			FMath::RandRange(MinLocation.Z, MaxLocation.Z));
		SetActorLocation(RandomLocation);
	}
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move(DeltaTime);
}

void AMovingPlatform::Move(float DeltaTime)
{
	FVector NormalizedDir = GetNormalizedWorldDir();
	FVector newLocation = GetActorLocation() + NormalizedDir * DirObserve * MoveSpeed * DeltaTime;
	FVector DeltaMove = newLocation - StartLocation;
	float dist = FVector::DotProduct(DeltaMove, NormalizedDir);
	if (dist < MinRange)
	{
		FVector MinLocation = StartLocation + NormalizedDir * MinRange;
		newLocation = MinLocation;
		DirObserve = 1;
	}
	else if (dist > MaxRange)
	{
		FVector MaxLocation = StartLocation + NormalizedDir * MaxRange;
		newLocation = MaxLocation;
		DirObserve = -1;
	}
	SetActorLocation(newLocation);
}

FVector AMovingPlatform::GetNormalizedWorldDir()
{
	return GetActorRotation().RotateVector(MoveDirection).GetSafeNormal();
}

