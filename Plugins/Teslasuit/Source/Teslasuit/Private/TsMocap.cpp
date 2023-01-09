// Fill out your copyright notice in the Description page of Project Settings.


#include "TsMocap.h"
#include <Async/Async.h>
#include "ITeslasuitPlugin.h"
#include "ts_api/ts_device_api.h"
#include "ts_api/ts_mocap_api.h"

static const auto BonesToTransform =
{
    //Suit bones
    TsBoneIndex::TsBoneIndex_Hips,
    TsBoneIndex::TsBoneIndex_UpperSpine,
    TsBoneIndex::TsBoneIndex_Spine,
    TsBoneIndex::TsBoneIndex_RightShoulder,
    TsBoneIndex::TsBoneIndex_RightUpperArm,
    TsBoneIndex::TsBoneIndex_RightLowerArm,
    TsBoneIndex::TsBoneIndex_RightHand,
    TsBoneIndex::TsBoneIndex_LeftUpperArm,
    TsBoneIndex::TsBoneIndex_LeftLowerArm,
    TsBoneIndex::TsBoneIndex_LeftHand,
    TsBoneIndex::TsBoneIndex_RightUpperLeg,
    TsBoneIndex::TsBoneIndex_RightLowerLeg,
    TsBoneIndex::TsBoneIndex_RightFoot,
    TsBoneIndex::TsBoneIndex_LeftUpperLeg,
    TsBoneIndex::TsBoneIndex_LeftLowerLeg,
    TsBoneIndex::TsBoneIndex_LeftFoot,

    //RightHand
    TsBoneIndex::TsBoneIndex_RightThumbProximal,
    TsBoneIndex::TsBoneIndex_RightThumbIntermediate,
    TsBoneIndex::TsBoneIndex_RightThumbDistal,
    TsBoneIndex::TsBoneIndex_RightIndexProximal,
    TsBoneIndex::TsBoneIndex_RightIndexIntermediate,
    TsBoneIndex::TsBoneIndex_RightIndexDistal,
    TsBoneIndex::TsBoneIndex_RightMiddleProximal,
    TsBoneIndex::TsBoneIndex_RightMiddleIntermediate,
    TsBoneIndex::TsBoneIndex_RightMiddleDistal,
    TsBoneIndex::TsBoneIndex_RightRingProximal,
    TsBoneIndex::TsBoneIndex_RightRingIntermediate,
    TsBoneIndex::TsBoneIndex_RightRingDistal,
    TsBoneIndex::TsBoneIndex_RightLittleProximal,
    TsBoneIndex::TsBoneIndex_RightLittleIntermediate,
    TsBoneIndex::TsBoneIndex_RightLittleDistal,

    //Left Hand
    TsBoneIndex::TsBoneIndex_LeftThumbProximal,
    TsBoneIndex::TsBoneIndex_LeftThumbIntermediate,
    TsBoneIndex::TsBoneIndex_LeftThumbDistal,
    TsBoneIndex::TsBoneIndex_LeftIndexProximal,
    TsBoneIndex::TsBoneIndex_LeftIndexIntermediate,
    TsBoneIndex::TsBoneIndex_LeftIndexDistal,
    TsBoneIndex::TsBoneIndex_LeftMiddleProximal,
    TsBoneIndex::TsBoneIndex_LeftMiddleIntermediate,
    TsBoneIndex::TsBoneIndex_LeftMiddleDistal,
    TsBoneIndex::TsBoneIndex_LeftRingProximal,
    TsBoneIndex::TsBoneIndex_LeftRingIntermediate,
    TsBoneIndex::TsBoneIndex_LeftRingDistal,
    TsBoneIndex::TsBoneIndex_LeftLittleProximal,
    TsBoneIndex::TsBoneIndex_LeftLittleIntermediate,
    TsBoneIndex::TsBoneIndex_LeftLittleDistal
};

decltype(&ts_mocap_start_streaming) StartMocapStreamingFn;
decltype(&ts_mocap_stop_streaming) StopMocapStreamingFn;
decltype(&ts_mocap_skeleton_calibrate) SkeletonCalibrateFn;
decltype(&ts_mocap_set_skeleton_update_callback) SetSkeletonUpdateCallback;
decltype(&ts_mocap_set_sensor_skeleton_update_callback) SetMocapSensorUpdateCallack;
decltype(&ts_mocap_skeleton_get_bone) SkeletonGetBone;
decltype(&ts_mocap_sensor_skeleton_get_bone) SkeletonGetSensorBone;

TsMocapBone UpdateBone;


UTsMocap::UTsMocap()
    : UObject()
{
    Initialize();
    UE_LOG(LogTemp, Log, TEXT("TsMocap: constructed."));
}

void UTsMocap::Initialize()
{
    auto LibHandle = ITeslasuitPlugin::Get().GetLibHandle();

    StartMocapStreamingFn = reinterpret_cast<decltype(&ts_mocap_start_streaming)>(
        FPlatformProcess::GetDllExport(LibHandle, *FString("ts_mocap_start_streaming")));
    StopMocapStreamingFn = reinterpret_cast<decltype(&ts_mocap_stop_streaming)>(
        FPlatformProcess::GetDllExport(LibHandle, *FString("ts_mocap_stop_streaming")));
    SkeletonCalibrateFn = reinterpret_cast<decltype(&ts_mocap_skeleton_calibrate)>(
        FPlatformProcess::GetDllExport(LibHandle, *FString("ts_mocap_skeleton_calibrate")));
    SetSkeletonUpdateCallback = reinterpret_cast<decltype(&ts_mocap_set_skeleton_update_callback)>(
        FPlatformProcess::GetDllExport(LibHandle, *FString("ts_mocap_set_skeleton_update_callback")));
    SetMocapSensorUpdateCallack = reinterpret_cast<decltype(&ts_mocap_set_sensor_skeleton_update_callback)>(
        FPlatformProcess::GetDllExport(LibHandle, *FString("ts_mocap_set_sensor_skeleton_update_callback")));
    SkeletonGetBone = reinterpret_cast<decltype(&ts_mocap_skeleton_get_bone)>(
        FPlatformProcess::GetDllExport(LibHandle, *FString("ts_mocap_skeleton_get_bone")));
    SkeletonGetSensorBone = reinterpret_cast<decltype(&ts_mocap_sensor_skeleton_get_bone)>(
        FPlatformProcess::GetDllExport(LibHandle, *FString("ts_mocap_sensor_skeletone_get_bone")));
    
    Data.Empty();
    for (const auto BoneIndex : BonesToTransform)
    {
        Data.Add(static_cast<FTsBoneIndex>(BoneIndex), FTransform());
    }
}

void UTsMocap::SetCallbacks()
{
    SetSkeletonUpdateCallback(static_cast<TsDeviceHandle*>(ts_device->Handle), [](TsDeviceHandle* handle, TsMocapSkeleton Skeleton, void* UserData)
    {
        auto Self = reinterpret_cast<UTsMocap*>(UserData);
        std::lock_guard<std::mutex> ALock(Self->AccessMutex);
        if (Self == nullptr || !Self->DeviceInitialized || !Self->bMocapRunning)
        {
            return;
        }
        for (const auto BoneIndex : BonesToTransform)
        {
            SkeletonGetBone(Skeleton, BoneIndex, &UpdateBone);
            auto& Transform = Self->Data[static_cast<FTsBoneIndex>(BoneIndex)];
            Transform.SetTranslation({ UpdateBone.position.x, UpdateBone.position.z, -UpdateBone.position.y });
            Transform.SetRotation({ UpdateBone.rotation.x, UpdateBone.rotation.z, -UpdateBone.rotation.y, UpdateBone.rotation.w });
        }
    }, this);
}

UTsMocap::~UTsMocap()
{
    std::lock_guard<std::mutex> lock(AccessMutex);
    if (DeviceInitialized && ts_device->IsConnected())
    {
        DeviceInitialized = false;
        StopMocap();
    }
    Data.Empty();
}

void UTsMocap::StartMocap()
{
    bMocapRunning = true;
    auto result = StartMocapStreamingFn(static_cast<TsDeviceHandle*>(ts_device->Handle));
    if (result != 0)
    {
        UE_LOG(LogTemp, Log, TEXT("TsMocap: start sreaming error %d"), result);
    }
}

void UTsMocap::StopMocap()
{
    auto Handle = static_cast<TsDeviceHandle*>(ts_device->Handle);
    SetSkeletonUpdateCallback(Handle, nullptr, nullptr);
    auto result = StopMocapStreamingFn(Handle);
    bMocapRunning = false;
    if (result != 0) 
    {
        UE_LOG(LogTemp, Log, TEXT("TsMocap: stop sreaming error %d"), result);
    }
}

void UTsMocap::Calibrate()
{
    auto result = SkeletonCalibrateFn(static_cast<TsDeviceHandle*>(ts_device->Handle));
    if (result != 0) 
    {
        UE_LOG(LogTemp, Log, TEXT("TsMocap: calibrate skeleton error %d"), result);
    }
}

void UTsMocap::GetMocapData(UTsMocap::MocapData& OutData) const
{
    std::lock_guard<std::mutex> lock(AccessMutex);
    OutData = Data;
}

void UTsMocap::SetTsDevice(UTsDevice* device)
{
    ts_device = device;
    DeviceInitialized = true;
    if (bMocapRunning)
    {
        StopMocap();
    }
    SetCallbacks();
    StartMocap();
}
