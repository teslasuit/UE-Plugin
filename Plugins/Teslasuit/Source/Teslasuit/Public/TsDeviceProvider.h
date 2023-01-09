#pragma once
#include <set>
#include <map>
#include <vector>
#include <atomic>
#include <thread>
#include <functional>

class UTsDevice;
class TsDeviceId;

/**
 * \addtogroup device
 * @{
 */

 /*!
	\brief Provides access to the device handles from Teslasuit C API library

	Class shouldn't be used directly.
	#FTeslasuitModule creates an instance of this class
	in order to	manage devices from signle place.
 */
class TESLASUIT_API TsDeviceProvider
{
	using Handles = std::map<TsDeviceId, void*>;
public:
	using Ids = std::set<TsDeviceId>;
	using ConnectCallback = std::function<void(const TsDeviceId&, void*)>;
    using DisconnectCallback = std::function<void(const TsDeviceId&)>;

public:
	TsDeviceProvider();
    ~TsDeviceProvider();

	// Client methods
	void SubscribeOnConnect(intptr_t subscriberID, const ConnectCallback& Cb);
    void SubscribeOnDisconnect(intptr_t subscriberID, const DisconnectCallback& Cb);
	void UnSubscribeOnConnect(intptr_t subscriberID);
	void UnSubscribeOnDisconnect(intptr_t subscriberID);
	const Ids& GetDeviceIds() const;
	void* GetDeviceHandle(const TsDeviceId& Id) const;

	// Configure methods
    void SetLibHandle(void* Handle);
    void Start();
    void Stop();

private:
	void UpdateDeviceList();
	void OnDeviceConnected(const TsDeviceId& Id);
    void OnDeviceDisconnected(const TsDeviceId& Id);
	void CloseDevices();
	
private:
	void* LibHandle = nullptr;
	std::atomic_bool bUpdateRunning = false;
	std::atomic_bool bUpdateFinished = false;
	std::thread UpdateThread;

	Ids DeviceIds;
	Handles DeviceHandles;

	std::map<intptr_t,ConnectCallback> ConnectCallbacks;
    std::map<intptr_t,DisconnectCallback> DisconnectCallbacks;
};

/**@}*/
