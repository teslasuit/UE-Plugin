#pragma once
#include "CoreMinimal.h"
#include "Runtime/Engine/Public/AnimationRuntime.h"
#include "Runtime/Engine/Public/Animation/AnimInstanceProxy.h"
#include "Runtime/AnimGraphRuntime/Public/BoneControllers/AnimNode_SkeletalControlBase.h"
#include "TsMocap.h"
#include "SkeletonBoneTransform.generated.h"

/**
 * \addtogroup mocap
 * @{
 */

 /*!
     \brief Stores pair of Unreal FBoneReference and #FTsBoneIndex.
  */
USTRUCT(Blueprintable)
struct FBonePair
{
    GENERATED_USTRUCT_BODY()
        
	UPROPERTY(EditAnywhere)
    FBoneReference BoneRef;
    
	UPROPERTY(EditAnywhere)
    FTsBoneIndex BoneIndex;
};

/*!
    \brief Applies provided transforms to animation.
 */
USTRUCT(BlueprintInternalUseOnly)
struct TESLASUIT_API FAnimNode_SkeletalBoneTransform: public FAnimNode_SkeletalControlBase
{
    GENERATED_USTRUCT_BODY()

public:
    FAnimNode_SkeletalBoneTransform();
    
public:
	int Num = 0;

public:
    virtual void GatherDebugData(FNodeDebugData& DebugData) override;
    virtual void EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms) override;
    virtual bool IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones) override;

private:
    virtual void InitializeBoneReferences(const FBoneContainer& RequiredBones) override;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teslasuit|Mocap")
    TArray<FBonePair> BonesToModify;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Offset)
    TMap<FTsBoneIndex, FQuat> RotationOffsets
    {
        {FTsBoneIndex::TsBoneIndex_Hips,          FQuat::MakeFromEuler(FVector(180, 90, 0)) },
        {FTsBoneIndex::TsBoneIndex_UpperSpine,    FQuat::MakeFromEuler(FVector(180, 90, 0)) },
        {FTsBoneIndex::TsBoneIndex_RightUpperArm, FQuat::MakeFromEuler(FVector(0, 90, 0)) },
        {FTsBoneIndex::TsBoneIndex_RightLowerArm, FQuat::MakeFromEuler(FVector(90, 90, 0)) },
        {FTsBoneIndex::TsBoneIndex_LeftUpperArm,  FQuat::MakeFromEuler(FVector(-180, -90, 0)) },
        {FTsBoneIndex::TsBoneIndex_LeftLowerArm,  FQuat::MakeFromEuler(FVector(90, -90, 0)) },
        {FTsBoneIndex::TsBoneIndex_RightHand,     FQuat::MakeFromEuler(FVector(-90, 90, 0)) },
        {FTsBoneIndex::TsBoneIndex_LeftHand,      FQuat::MakeFromEuler(FVector(90, -90, 0)) },
        {FTsBoneIndex::TsBoneIndex_RightUpperLeg, FQuat::MakeFromEuler(FVector(0, -90, 0)) },
        {FTsBoneIndex::TsBoneIndex_RightLowerLeg, FQuat::MakeFromEuler(FVector(0, -90, 0)) },
        {FTsBoneIndex::TsBoneIndex_LeftUpperLeg,  FQuat::MakeFromEuler(FVector(180, 90, 0)) },
        {FTsBoneIndex::TsBoneIndex_LeftLowerLeg,  FQuat::MakeFromEuler(FVector(180, 90, 0)) },
        {FTsBoneIndex::TsBoneIndex_RightFoot,     FQuat::MakeFromEuler(FVector(0, -90, 0)) },
        {FTsBoneIndex::TsBoneIndex_LeftFoot,      FQuat::MakeFromEuler(FVector(180, 90, 0)) }
    };

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rotation, meta = (PinShownByDefault))
    TMap<FTsBoneIndex, FTransform> data;
};

/**@}*/