#pragma once
#include "../Common.h"
#include "ComponentIncludes.h"

class TimeSince: public CCommon, public LComponent {
	
public:
	float GetTimeSince();
	void SetTimeSince(float);
	TimeSince();

	TimeSince& operator=(const float& rhs)
	{
		SetTimeSince(rhs);
		return *this;
	}

private:
	float m_fTime;

};