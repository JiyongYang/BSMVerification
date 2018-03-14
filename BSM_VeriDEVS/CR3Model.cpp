#include "CR3Model.h"
#include "CLauMessage.h"

std::string CR3Model::M3_i_EL = "M3_In_EL";
std::string CR3Model::M3_i_ES = "M3_In_ES";
std::string CR3Model::M3_o_RESULT = "M3_out_RESULT";


CR3Model::CR3Model()
{
	SetName("R3 Model");

	m_state = WAIT;

	// Input
	AddInPorts(1, M3_i_EL.c_str());
	AddInPorts(1, M3_i_ES.c_str());

	// Output
	AddOutPorts(1, M3_o_RESULT.c_str());

	Td = 10;
}


CR3Model::~CR3Model()
{
}

bool CR3Model::ExtTransFn(const CDEVSimMessage & msg)
{
	if (m_state == WAIT)
	{
		//CLauMessage* pMsg = (CLauMessage*)msg.GetArg(0);
		if (msg.GetPort() == M3_i_ES)
		{
			std::cout << "\n     ## [Notice] : " << "DETECTING ENEMY AIRCRAFT" << std::endl << std::endl;
			m_state = DETECTED;
		}
		
		if (msg.GetPort() == M3_i_EL)
		{
			m_state = FAIL;
		}
	}
	else if (m_state == DETECTED)
	{
		if(msg.GetPort() == M3_i_EL)
		{
			m_state = PASS;
		}
	}

	return true;
}

bool CR3Model::IntTransFn()
{
	// timeout
	if (m_state == DETECTED)
	{
		m_state = FAIL;
	}
	// PASS
	else if (m_state == PASS)
	{
		m_state = END;
	}
	// FAIL
	else if (m_state == FAIL)
	{
		m_state = END;
	}
	else if (m_state == END)
	{
		// *
	}
	return true;
}

bool CR3Model::OutputFn(CDEVSimMessage & msg)
{
	if (m_state == DETECTED)
	{
		std::cout << "\n     ## [Notice] : " << "RESULT msg--TIMEOUT" << std::endl << std::endl;
		// timeout
		msg.SetPortValue(M3_o_RESULT.c_str(), new CLauMessage(-1));
	}
	else if (m_state == PASS)
	{
		std::cout << "\n     ## [Notice] : " << "RESULT msg--PASS" << std::endl << std::endl;
		// pass
		msg.SetPortValue(M3_o_RESULT.c_str(), new CLauMessage(1));
	}
	else if (m_state == FAIL)
	{
		std::cout << "\n     ## [Notice] : " << "RESULT msg--FAIL" << std::endl << std::endl;
		// fail
		msg.SetPortValue(M3_o_RESULT.c_str(), new CLauMessage(0));
	}
	else if (m_state == END)
	{
		std::cout << "\n     ## [Notice] : " << "RESULT msg--END" << std::endl << std::endl;
		// *
	}
	return true;
}

TimeType CR3Model::TimeAdvanceFn()
{
	if (m_state == WAIT)
		return Infinity;
	else if (m_state == DETECTED)
		return Td;
	else if (m_state == PASS)
		return 0;
	else if (m_state == FAIL)
		return 0;
	else if (m_state == END)
		return Infinity;
}