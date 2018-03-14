#include <iostream>
#include "DEVSim.h"
#include "COutmost.h"

int main()
{
	CREATE_LOG_STD(CAT_ALL, LOG_DEBUG); // ȭ�鿡�� BANKSIM �α׸� ǥ��

										// DEVSimInterface ����
	CDEVSimInterface* pInterface = CDEVSimInterfaceDefaultFactory::create();
	SET_DEVSINTERFACE(pInterface);

	pInterface->SimOption.TimeMode = CSimOption::SECOND;
	pInterface->SimOption.bRealtime = false;
	pInterface->SimOption.bMultiThread = false;

	CCoupled* model = new COutmost;
	pInterface->SetModel(model);

	pInterface->SimulationStart();

	//pInterface->SimOption.bMultiThread = false; �̹Ƿ�
	// ���� �Լ����� ����ñ��� Blocking
	pInterface->EngineStart();


	// �� ����
	delete pInterface->GetModel();
	pInterface->SetModel(NULL);

	CDEVSimInterfaceDefaultFactory::destroy(pInterface);
	pInterface = NULL;
}