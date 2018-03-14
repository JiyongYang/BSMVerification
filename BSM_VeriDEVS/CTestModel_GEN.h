#pragma once
#include "DEVSim.h"

class CTestModel_GEN : public CAtomic
{
public:
	CTestModel_GEN();
	~CTestModel_GEN();

public:
	virtual bool ExtTransFn(const CDEVSimMessage &);
	virtual bool IntTransFn();
	virtual bool OutputFn(CDEVSimMessage &);
	virtual TimeType TimeAdvanceFn();

public:
	enum SysState { GEN, END };
	SysState m_state;

	double preT;

public:
	static std::string TM_i_RESULT;

	static std::string TM_o_LE;
	static std::string TM_o_MI;

	// missile default value
	double mx;
	double my;
	double mz;

	// enemy aircraft default value
	double ex;
	double ey;
	double ez;

	// flg
	int flg;

	// offset
	double offset;
};

