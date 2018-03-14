#pragma once
#include "DEVSim.h"

typedef struct
{
	double x;
	double y;
	double z;

} Position;

class CLocMessage : public SMSL::CObject
{
public:
	CLocMessage(Position _pos, int _type) :pos(_pos), type(_type) {}
	~CLocMessage() {}

public:
	Position pos;
	int type;
};