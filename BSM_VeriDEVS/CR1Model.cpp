#include "CR1Model.h"
#include "CLocMessage.h"
#include "CLauMessage.h"
#include <cmath>

std::string CR1Model::M1_i_LE = "M1_In_LE";
std::string CR1Model::M1_o_ES = "M1_Out_ES";

double distance(const Position& p1, const Position& p2);

CR1Model::CR1Model()
{
	SetName("R1 Model");

	m_state = DETECTING;

	// Input
	AddInPorts(1, M1_i_LE.c_str());

	// Output
	AddOutPorts(1, M1_o_ES.c_str());

	RadorMsg = 0;
	EnermyMsg = 0;

	RequiredDis = 500;

	RadorPos = { 0, };
	EnermyPos = { 0, };
}


CR1Model::~CR1Model()
{
}


bool CR1Model::ExtTransFn(const CDEVSimMessage & msg)
{
	if (m_state == DETECTING)
	{
		CLocMessage* pMsg = (CLocMessage*)msg.GetArg(0);

		// Rador
		if (pMsg->type == 1)
		{
			RadorPos = pMsg->pos;
			RadorMsg = 1;
		}
		// Enermy Aircraft
		else if (pMsg->type == 2)
		{
			EnermyPos = pMsg->pos;
			EnermyMsg = 1;
		}

		// Successfully Rador msg & Enermy msg receive
		if (RadorMsg == 1 && EnermyMsg == 1)
		{
			double dis = distance(RadorPos, EnermyPos);

			std::cout << "\n     ## [Notice] : " << "Distance between RADOR and AIRCRAFT--" << dis << std::endl << std::endl;

			if (dis <= RequiredDis)
			{
				m_state = DETECTED;
				std::cout << "\n     ## [Notice] : " << "DETECTING ENEMY AIRCRAFT" << std::endl << std::endl;
			}

			RadorMsg = 0;
			EnermyMsg = 0;
		}
	}

	return true;
}

bool CR1Model::IntTransFn()
{
	if (m_state == DETECTED)
	{
		m_state = END;
	}
	else if (m_state == END)
	{
		// *
	}
	return true;
}

bool CR1Model::OutputFn(CDEVSimMessage & msg)
{
	if (m_state == DETECTED)
	{
		// generate Es
		msg.SetPortValue(M1_o_ES.c_str(), new CLauMessage(1));
	}
	else if (m_state == END)
	{
		// *
	}
	return true;
}

TimeType CR1Model::TimeAdvanceFn()
{
	if (m_state == DETECTING)
		return Infinity;
	else if (m_state == DETECTED)
		return 0;
	else if (m_state == END)
		return Infinity;
}

double distance(const Position& p1, const Position& p2)
{
	double distance;

	distance = sqrt(pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2) + pow((p1.z - p2.z), 2));

	return distance;
}