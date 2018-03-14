#pragma once

#include "DEVSim.h"
#include <string>

class CR3Model : public CAtomic
{
public:
	CR3Model();
	~CR3Model();

public:
	virtual bool ExtTransFn(const CDEVSimMessage &);
	virtual bool IntTransFn();
	virtual bool OutputFn(CDEVSimMessage &);
	virtual TimeType TimeAdvanceFn();

public:
	enum SysState { WAIT, DETECTED, PASS, FAIL, END };
	SysState m_state;

public:
	static std::string M3_i_ES;
	static std::string M3_i_EL;
	static std::string M3_o_RESULT;

	double Td;
};

