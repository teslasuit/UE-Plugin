// Fill out your copyright notice in the Description page of Project Settings.


#include "TsPpg.h"
#include <Async/Async.h>
#include "ITeslasuitPlugin.h"
#include "ts_api/ts_device_api.h"
#include "ts_api/ts_biometry_api.h"
#include <vector>


TsPpgData PpgData;

decltype(&ts_ppg_raw_start_streaming) StartPPGStreamingFn;
decltype(&ts_ppg_raw_stop_streaming) StopPPGStreamingFn;
decltype(&ts_ppg_calibrate) CalibratePPGFn;
decltype(&ts_ppg_set_update_callback) SetPpgUpdateCallback;
decltype(&ts_ppg_get_heart_rate) GetHeartRateFn;
decltype(&ts_ppg_get_oxygen_percent) GetOxygenPercentFn;
decltype(&ts_ppg_get_number_of_nodes) GetPPGNumberOfNodesFn;
decltype(&ts_ppg_get_node_indexes) GetPPGNodeIndexesFn;


UTsPpg::UTsPpg()
    : UObject()
{
    Initialize();
    UE_LOG(LogTemp, Log, TEXT("UTsPpg: constructed."));
}

void UTsPpg::Initialize()
{
    auto LibHandle = ITeslasuitPlugin::Get().GetLibHandle();

    StartPPGStreamingFn = reinterpret_cast<decltype(&ts_ppg_raw_start_streaming)>(
        FPlatformProcess::GetDllExport(LibHandle, *FString("ts_ppg_raw_start_streaming")));
    StopPPGStreamingFn = reinterpret_cast<decltype(&ts_ppg_raw_stop_streaming)>(
        FPlatformProcess::GetDllExport(LibHandle, *FString("ts_ppg_raw_stop_streaming")));
    CalibratePPGFn = reinterpret_cast<decltype(&ts_ppg_calibrate)>(
        FPlatformProcess::GetDllExport(LibHandle, *FString("ts_ppg_calibrate")));
    SetPpgUpdateCallback = reinterpret_cast<decltype(&ts_ppg_set_update_callback)>(
        FPlatformProcess::GetDllExport(LibHandle, *FString("ts_ppg_set_update_callback")));
    GetHeartRateFn = reinterpret_cast<decltype(&ts_ppg_get_heart_rate)>(
        FPlatformProcess::GetDllExport(LibHandle, *FString("ts_ppg_get_heart_rate")));
    GetOxygenPercentFn = reinterpret_cast<decltype(&ts_ppg_get_oxygen_percent)>(
        FPlatformProcess::GetDllExport(LibHandle, *FString("ts_ppg_get_oxygen_percent")));
    GetPPGNumberOfNodesFn = reinterpret_cast<decltype(&ts_ppg_get_number_of_nodes)>(
        FPlatformProcess::GetDllExport(LibHandle, *FString("ts_ppg_get_number_of_nodes")));
    GetPPGNodeIndexesFn = reinterpret_cast<decltype(&ts_ppg_get_node_indexes)>(
        FPlatformProcess::GetDllExport(LibHandle, *FString("ts_ppg_get_node_indexes")));
}

void UTsPpg::SetCallbacks()
{
    SetPpgUpdateCallback(static_cast<TsDeviceHandle*>(ts_device->Handle), [](TsDeviceHandle* Device, TsPpgData Ppg, void* UserData)
    {
        auto Self = reinterpret_cast<UTsPpg*>(UserData);
        std::lock_guard<std::mutex> ALock(Self->AccessMutex);
        if (Self == nullptr || !Self->DeviceInitialized || !Self->bPpgRunning)
        {
            return;
        }

        uint8_t count;
        GetPPGNumberOfNodesFn(Ppg, &count);

        std::vector<uint8_t> nodes(10);
        GetPPGNodeIndexesFn(Ppg, nodes.data(), nodes.size());

        if (count > 0)
        {
            uint32_t heartrate;
            GetHeartRateFn(Ppg, nodes[0], &heartrate);

            uint8_t oxygen;
            GetOxygenPercentFn(Ppg, nodes[0], &oxygen);

            Self->Heartrate = heartrate;
            Self->OxygenPercent = oxygen;
        }
    }, this);
}

UTsPpg::~UTsPpg()
{
    std::lock_guard<std::mutex> lock(AccessMutex);
    if (DeviceInitialized && ts_device->Handle)
    {
        DeviceInitialized = false;
        StopPpg();
    }
}

void UTsPpg::StartPpg()
{
    bPpgRunning = true;
    auto result = StartPPGStreamingFn(static_cast<TsDeviceHandle*>(ts_device->Handle));
    if (result != 0)
    {
        UE_LOG(LogTemp, Log, TEXT("UTsPpg: start sreaming error %d"), result);
    }
}

void UTsPpg::StopPpg()
{
    auto Handle = static_cast<TsDeviceHandle*>(ts_device->Handle);
    SetPpgUpdateCallback(Handle, nullptr, nullptr);
    auto result = StopPPGStreamingFn(Handle);
    bPpgRunning = false;
    if (result != 0) 
    {
        UE_LOG(LogTemp, Log, TEXT("UTsPpg: stop sreaming error %d"), result);
    }
}

void UTsPpg::Calibrate()
{
    auto result = CalibratePPGFn(static_cast<TsDeviceHandle*>(ts_device->Handle));
    if (result != 0)
    {
        UE_LOG(LogTemp, Log, TEXT("UTsPpg: calibrate error %d"), result);
    }
}

void UTsPpg::SetTsDevice(UTsDevice* device)
{
    ts_device = device;
    DeviceInitialized = true;
    if (bPpgRunning)
    {
        StopPpg();
    }
    SetCallbacks();
    StartPpg();
}
