#include "Motion/SkeletonBoneTransform.h"

#define LOCTEXT_NAMESPACE "Teslasuit"  


FAnimNode_SkeletalBoneTransform::FAnimNode_SkeletalBoneTransform()
{
	Num = BonesToModify.Num();
}

void FAnimNode_SkeletalBoneTransform::GatherDebugData(FNodeDebugData & DebugData)
{
}

void FAnimNode_SkeletalBoneTransform::EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext & Output, TArray<FBoneTransform>& OutBoneTransforms)
{
    check(OutBoneTransforms.Num() == 0);
    TArray<FBoneTransform> bone_transform;
    bone_transform.Add(FBoneTransform());
    const FBoneContainer& BoneContainer = Output.Pose.GetPose().GetBoneContainer();

    for (auto& object: BonesToModify)
    {
        if (data.Contains(object.BoneIndex))
        {
            const auto transform = data[object.BoneIndex];

            FTransform component_transform = Output.AnimInstanceProxy->GetComponentTransform();
            FCompactPoseBoneIndex CompactPose = object.BoneRef.GetCompactPoseIndex(BoneContainer);
            FTransform NewBone = Output.Pose.GetComponentSpaceTransform(FCompactPoseBoneIndex(object.BoneRef.BoneIndex));

            if (RotationOffsets.Contains(object.BoneIndex))
            {
                NewBone.SetRotation(transform.GetRotation() * RotationOffsets[object.BoneIndex]);
            }
            else
            {
                NewBone.SetRotation(transform.GetRotation());
            }
            
            bone_transform[0] = FBoneTransform(object.BoneRef.GetCompactPoseIndex(BoneContainer), NewBone);
            Output.Pose.LocalBlendCSBoneTransforms(bone_transform, 1.0f);
        }
    }
}

bool FAnimNode_SkeletalBoneTransform::IsValidToEvaluate(const USkeleton * Skeleton, const FBoneContainer & RequiredBones)
{
    for (auto& bone : BonesToModify)
    {
        if (!bone.BoneRef.IsValidToEvaluate(RequiredBones))
            return false;
    }
    return true;
}

void FAnimNode_SkeletalBoneTransform::InitializeBoneReferences(const FBoneContainer& RequiredBones)
{
    for (auto& object: BonesToModify)
    {
        object.BoneRef.Initialize(RequiredBones);
    }
}

#undef LOCTEXT_NAMESPACE  