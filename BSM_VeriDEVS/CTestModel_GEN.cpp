#include "CTestModel_GEN.h"
#include "CLauMessage.h"
#include "CLocMessage.h"

std::string CTestModel_GEN::TM_i_RESULT = "TM_In_REUSLT";
std::string CTestModel_GEN::TM_o_LE = "TM_Out_LE";
std::string CTestModel_GEN::TM_o_MI = "TM_Out_MI";


CTestModel_GEN::CTestModel_GEN()
{
	SetName("TESTModel_GEN");

	preT = 0.5;

	// Input
	AddInPorts(1, TM_i_RESULT.c_str());

	// Output
	AddOutPorts(1, TM_o_LE.c_str());
	AddOutPorts(1, TM_o_MI.c_str());

	m_state = GEN;

	mx = 0;
	my = 0;
	mz = 0;

	ex = 500;
	ey = 500;
	ez = 500;

	flg = 1;
	offset = 10;
}


CTestModel_GEN::~CTestModel_GEN()
{
}

bool CTestModel_GEN::ExtTransFn(const CDEVSimMessage & msg)
{
	if (m_state == GEN)
	{
		CLauMessage* pMsg = (CLauMessage*)msg.GetArg(0);

		if (pMsg->flg == 1)
		{
			std::cout << "\n     ## [FINAL RESULT] : " << "PASS" << std::endl << std::endl;
		}
		else if (pMsg->flg == 0)
		{
			std::cout << "\n     ## [FINAL RESULT] : " << "FAIL" << std::endl << std::endl;
		}
		else if (pMsg->flg == -1)
		{
			std::cout << "\n     ## [FINAL RESULT] : " << "TIMEOUT" << std::endl << std::endl;
		}

		m_state = END;
	}
	return true;
}

bool CTestModel_GEN::IntTransFn()
{
	if (m_state == GEN)
	{
		m_state = GEN;
	}

	return true;
}

bool CTestModel_GEN::OutputFn(CDEVSimMessage & msg)
{
	if (m_state == GEN)
	{
		CLocMessage *LocM;

		if (flg % 2 == 0)
		{
			// Gen random pos
			Position pos;
			pos.x = mx + offset;
			pos.y = my + offset;
			pos.z = mz + offset;

			mx += offset;
			my += offset;
			mz += offset;

			LocM = new CLocMessage(pos, 1);

		}
		else
		{
			Position pos;
			pos.x = ex - offset;
			pos.y = ey - offset;
			pos.z = ez - offset;

			ex -= offset;
			ey -= offset;
			ez -= offset;

			LocM = new CLocMessage(pos, 2);
		}
		msg.SetPortValue(TM_o_LE.c_str(), LocM);

		flg += 1;

		if (flg > 30)
		{
			// launched
			CLauMessage * LauM = new CLauMessage(1);

			// not launched
			// CLauMessage * LauM = new CLauMessage(0);

			msg.SetPortValue(TM_o_MI.c_str(), LauM);
		}
	}

	return true;
}

TimeType CTestModel_GEN::TimeAdvanceFn()
{
	if (m_state == GEN)
		return preT;
	else if (m_state == END)
		return Infinity;
}
