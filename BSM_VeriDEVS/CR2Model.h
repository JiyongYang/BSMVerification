#pragma once

#include "DEVSim.h"
#include <string>

class CR2Model : public CAtomic
{
public:
	CR2Model();
	~CR2Model();

public:
	virtual bool ExtTransFn(const CDEVSimMessage &);
	virtual bool IntTransFn();
	virtual bool OutputFn(CDEVSimMessage &);
	virtual TimeType TimeAdvanceFn();

public:
	enum SysState { STOP, LAUNCH, END };
	SysState m_state;

public:
	static std::string M2_i_MI;
	static std::string M2_o_EL;
};

