#pragma once

#if ENGINE_MAJOR_VERSION > 4
	#include "Editor/AnimGraph/Public/AnimGraphNode_SkeletalControlBase.h"
#else
	#include "Editor/AnimGraph/Classes/AnimGraphNode_SkeletalControlBase.h"
#endif
#include "Motion/SkeletonBoneTransform.h"
#include "SkeletonBoneTransformGraph.generated.h"



UCLASS(meta = (Keywords = "MotionAnimation"))
class TESLASUITEDITOR_API UAnimGraphNode_SkeletalBoneTransform : public UAnimGraphNode_SkeletalControlBase
{
	GENERATED_UCLASS_BODY()
	UPROPERTY(EditAnywhere, Category = Settings)
	FAnimNode_SkeletalBoneTransform Node;
public:
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FText GetTooltipText() const override;
protected:
	virtual FText GetControllerDescription() const override;
	virtual const FAnimNode_SkeletalControlBase* GetNode() const override { return &Node; }

};