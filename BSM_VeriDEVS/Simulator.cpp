#include <iostream>
#include "DEVSim.h"
#include "COutmost.h"

int main()
{
	CREATE_LOG_STD(CAT_ALL, LOG_DEBUG); // 화면에는 BANKSIM 로그만 표시

										// DEVSimInterface 설정
	CDEVSimInterface* pInterface = CDEVSimInterfaceDefaultFactory::create();
	SET_DEVSINTERFACE(pInterface);

	pInterface->SimOption.TimeMode = CSimOption::SECOND;
	pInterface->SimOption.bRealtime = false;
	pInterface->SimOption.bMultiThread = false;

	CCoupled* model = new COutmost;
	pInterface->SetModel(model);

	pInterface->SimulationStart();

	//pInterface->SimOption.bMultiThread = false; 이므로
	// 다음 함수에서 종료시까지 Blocking
	pInterface->EngineStart();


	// 모델 삭제
	delete pInterface->GetModel();
	pInterface->SetModel(NULL);

	CDEVSimInterfaceDefaultFactory::destroy(pInterface);
	pInterface = NULL;
}