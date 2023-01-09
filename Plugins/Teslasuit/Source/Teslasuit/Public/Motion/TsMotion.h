#pragma once
#include "CoreMinimal.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Runtime/Engine/Classes/Components/ActorComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Animation/AnimBlueprintGeneratedClass.h"
#include "Motion/TsMotionAnimation.h"
#include "TsMocap.h"
#include "TsMotion.generated.h"

/**
 * \addtogroup mocap
 * @{
 */

 /*!
	 \brief Motion component that should be applied to an actor.

	 Uses #UTsMocap to receive motion data from device.
	 Applies motion to assigned actor using #UTsMotionAnimation.
  */
UCLASS(ClassGroup = Teslasuit, Category = "Teslasuit", meta = (BlueprintSpawnableComponent))
class TESLASUIT_API UTsMotion : public UActorComponent
{
    GENERATED_BODY()

public:
	UTsMotion();
    ~UTsMotion();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teslasuit|Mocap")
	TSubclassOf<UTsMotionAnimation> AnimationClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teslasuit|Mocap")
	UTsMocap* mocap;

	UFUNCTION(BlueprintCallable, Category = "Teslasuit|Biometry")
	void SetSkeletalMesh(USkeletalMeshComponent* skeletalMesh);
protected:
    virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    virtual void UninitializeComponent() override;
    
private:
	UTsMotionAnimation* MotionAnimation;
	USkeletalMeshComponent* SkeletalMesh;


	FTimerHandle TickCallibrationTimer;
	FTimerHandle StopCallibrationTimer;
};

/**@}*/
