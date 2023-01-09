#include "Motion/SkeletonBoneTransformGraph.h"


#define LOCTEXT_NAMESPACE "TeslasuitEditor"
UAnimGraphNode_SkeletalBoneTransform::UAnimGraphNode_SkeletalBoneTransform(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

}
FText UAnimGraphNode_SkeletalBoneTransform::GetControllerDescription() const
{
	return LOCTEXT("Teslasuit", "Teslasuit");
}
FText UAnimGraphNode_SkeletalBoneTransform::GetTooltipText() const
{
	return LOCTEXT("Teslasuit", "Teslasuit");
}
FText UAnimGraphNode_SkeletalBoneTransform::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return GetControllerDescription();
}
#undef LOCTEXT_NAMESPACE