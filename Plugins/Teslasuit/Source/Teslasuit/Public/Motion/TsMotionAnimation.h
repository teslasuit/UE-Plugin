#pragma once
#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Animation/AnimInstance.h"
#include "TsMocap.h"
#include "TsMotionAnimation.generated.h"

/**
 * \addtogroup mocap
 * @{
 */

 /*!
     \brief Motion animation that might be applied to an actor to transform it according to a suit.
  */
UCLASS()
class TESLASUIT_API UTsMotionAnimation: public UAnimInstance
{
    GENERATED_BODY()

public:
	UTsMotionAnimation(const FObjectInitializer& ObjectInitializer);

    virtual void NativeInitializeAnimation() override;

    virtual void NativeUpdateAnimation(float DeltaTimeX) override;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teslasuit")
    TMap<FTsBoneIndex, FTransform> data;
};

/**@}*/
