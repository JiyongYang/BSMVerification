#pragma once
#include "DEVSim.h"


class CLauMessage : public SMSL::CObject
{
public:
	CLauMessage(int data) : flg(data) {}
	~CLauMessage() {}

public:
	int flg;
};