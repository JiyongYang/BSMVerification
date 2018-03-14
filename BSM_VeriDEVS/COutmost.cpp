#include "COutmost.h"
#include "DyVeriModel.h"
#include "CTestModel_GEN.h"

COutmost::COutmost()
{
	SetName("Outmost Model");


	// Model
	CModel *pTestModel = new CTestModel_GEN;
	AddComponent(1, pTestModel);

	CModel *pDyVeriModel = new DyVeriModel;
	AddComponent(1, pDyVeriModel);


	// Coupling
	// Internal
	AddCoupling(pTestModel, CTestModel_GEN::TM_o_LE.c_str(),
		pDyVeriModel, DyVeriModel::DV_i_LE.c_str());

	AddCoupling(pTestModel, CTestModel_GEN::TM_o_MI.c_str(),
		pDyVeriModel, DyVeriModel::DV_i_MI.c_str());

	AddCoupling(pDyVeriModel, DyVeriModel::DV_o_RESULT.c_str(),
		pTestModel, CTestModel_GEN::TM_i_RESULT.c_str());

}


COutmost::~COutmost()
{
}
