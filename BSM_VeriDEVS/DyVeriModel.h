#pragma once
#include "DEVSim.h"

class DyVeriModel : public CCoupled
{
public:
	DyVeriModel();
	~DyVeriModel();

	static std::string DV_i_LE;
	static std::string DV_i_MI;

	static std::string DV_o_RESULT;
};

