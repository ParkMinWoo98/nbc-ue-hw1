#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class HW1_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	AMovingPlatform();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Platform|Components")
	USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform|Components")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform|Properties")
	FVector MoveDirection;
	int DirObserve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Platform|Properties")
	float MoveSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform|Properties")
	float MinRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform|Properties")
	float MaxRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform|Properties")
	bool StartRandomInRange;
	FVector StartLocation;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void Move(float DeltaTime);

	FVector GetNormalizedWorldDir();
};
