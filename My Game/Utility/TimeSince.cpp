#include "TimeSince.h"

TimeSince::TimeSince() {
	m_fTime = m_pTimer->GetTime();
}

float TimeSince::GetTimeSince() {
	return m_pTimer->GetTime() - m_fTime;
}

void TimeSince::SetTimeSince(float f) {
	m_fTime = m_pTimer->GetTime() - f;
}
