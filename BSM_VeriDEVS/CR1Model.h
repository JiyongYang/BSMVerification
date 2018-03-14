#pragma once

#include "DEVSim.h"
#include <string>

#include "CLocMessage.h"

class CR1Model : public CAtomic
{
public:
	CR1Model();
	~CR1Model();

public:
	virtual bool ExtTransFn(const CDEVSimMessage &);
	virtual bool IntTransFn();
	virtual bool OutputFn(CDEVSimMessage &);
	virtual TimeType TimeAdvanceFn();

public:
	enum SysState { DETECTING, DETECTED, END };
	SysState m_state;

public:
	static std::string M1_i_LE;
	static std::string M1_o_ES;

	int RadorMsg;
	int EnermyMsg;

	double RequiredDis;

	Position RadorPos;
	Position EnermyPos;
};

