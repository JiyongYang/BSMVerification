#include "CR2Model.h"
#include "CLauMessage.h"

std::string CR2Model::M2_i_MI = "M2_In_MI";
std::string CR2Model::M2_o_EL = "M2_Out_EL";


CR2Model::CR2Model()
{
	SetName("R2 Model");

	m_state = STOP;

	// Input
	AddInPorts(1, M2_i_MI.c_str());

	// Output
	AddOutPorts(1, M2_o_EL.c_str());

}


CR2Model::~CR2Model()
{
}

bool CR2Model::ExtTransFn(const CDEVSimMessage & msg)
{
	if (m_state == STOP)
	{
		CLauMessage* pMsg = (CLauMessage*)msg.GetArg(0);

		if (pMsg->flg == 1)
		{
			m_state = LAUNCH;

			
		}
	}

	return true;
}

bool CR2Model::IntTransFn()
{
	if (m_state == LAUNCH)
	{
		m_state = END;
	}
	else if (m_state == END)
	{
		// *
	}
	return true;
}

bool CR2Model::OutputFn(CDEVSimMessage & msg)
{
	if (m_state == LAUNCH)
	{
		// generate El
		msg.SetPortValue(M2_o_EL.c_str(), new CLauMessage(1));
		std::cout << "\n     ## [Notice] : " << "LAUNCHING MISSILE" << std::endl << std::endl;
	}
	else if (m_state == END)
	{
		// *
	}
	return true;
}

TimeType CR2Model::TimeAdvanceFn()
{
	if (m_state == STOP)
		return Infinity;
	else if (m_state == LAUNCH)
		return 0;
	else if (m_state == END)
		return Infinity;
}
