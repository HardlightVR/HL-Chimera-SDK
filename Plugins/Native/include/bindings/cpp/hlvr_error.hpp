#pragma once

#include "HLVR.h"

namespace hlvr 
{

class status_code {
public:
	explicit status_code(HLVR_Result result) : m_code{ result } {}
	status_code() = default;
	const char* what() const {
		return HLVR_ErrorString(m_code);
	}
	const HLVR_Result value() const {
		return m_code;
	}
	explicit operator bool() const noexcept{
		return HLVR_OK(m_code);
	}
private:
	HLVR_Result m_code;
};


}