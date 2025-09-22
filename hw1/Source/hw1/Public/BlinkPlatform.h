#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "BlinkPlatform.generated.h"

UCLASS()
class HW1_API ABlinkPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	ABlinkPlatform();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Platform|Components")
	USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform|Components")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform|Properties")
	float DurationShow;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform|Properties")
	float DurationHide;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform|Properties")
	float MaxInitialDelay;			// 맨 처음에는 0 ~ MaxInitialDelay 랜덤한 시간만큼 Show

	FTimerHandle TimerHandle;
	bool bShow;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void ShowPlatform(bool bShow, bool bSetTimer = true);
	void SwitchBlink();
};
