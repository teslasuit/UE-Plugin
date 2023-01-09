#pragma once
#include <cstdint>

/**
 * \addtogroup device
 * @{
 */

 /*!
	 \brief Unique Teslasuit device id.

	 Wrapper of unique device id with convinient methods,
	 such as: compare operators, copy, conversion to string.
 */
class TESLASUIT_API TsDeviceId
{
	using UnderlyingType = std::uint8_t;
    static const std::size_t UnderlyingSize = 16;
public:
	TsDeviceId();
	TsDeviceId(const UnderlyingType* RawData, std::size_t Size = UnderlyingSize);
	TsDeviceId(const TsDeviceId& Other);
	TsDeviceId& operator=(const TsDeviceId& Other);
	bool operator==(const TsDeviceId& Other) const;
    bool operator<(const TsDeviceId& Other) const;

	const UnderlyingType* GetData() const;
	void Reset();
	FString ToString() const;

private:
	UnderlyingType Data[UnderlyingSize];
};

/**@}*/
