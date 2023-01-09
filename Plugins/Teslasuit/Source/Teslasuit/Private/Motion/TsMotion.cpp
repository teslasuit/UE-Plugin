#include "Motion/TsMotion.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/UMG/Public/Components/WidgetComponent.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"

UTsMotion::UTsMotion()
	: UActorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;
}

UTsMotion::~UTsMotion()
{
}

void UTsMotion::SetSkeletalMesh(USkeletalMeshComponent* skeletalMesh)
{
	if (skeletalMesh == nullptr)
		SkeletalMesh = Cast<USkeletalMeshComponent>(GetOwner()->GetComponentByClass(USkeletalMeshComponent::StaticClass()));
	else
		SkeletalMesh = skeletalMesh;

	if (SkeletalMesh == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Skeletal mesh not found! MappedSkeletalMesh can only be attched to Actor with USkeletalMeshComponent. Destroying..."));
		DestroyComponent(false);
		return;
	}
	if (AnimationClass)
	{
		SkeletalMesh->SetAnimInstanceClass(AnimationClass);
		SkeletalMesh->InitAnim(true);
	}
}

void UTsMotion::BeginPlay()
{
    Super::BeginPlay();

	mocap = NewObject<UTsMocap>();

	SetSkeletalMesh(nullptr);
}

void UTsMotion::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
}

void UTsMotion::UninitializeComponent()
{

}

void UTsMotion::TickComponent
(
	float DeltaTime,
	enum ELevelTick TickType,
	FActorComponentTickFunction * ThisTickFunction
)
{
	if (MotionAnimation)
	{
		if (mocap->DeviceInitialized)
		{
			mocap->GetMocapData(MotionAnimation->data);
		}
	}
	else
	{
		MotionAnimation = Cast< UTsMotionAnimation>(SkeletalMesh->GetAnimInstance());
	}
}

