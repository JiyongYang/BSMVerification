#include "DyVeriModel.h"
#include "CR1Model.h"
#include "CR2Model.h"
#include "CR3Model.h"

std::string DyVeriModel::DV_i_LE = "DV_In_LE";
std::string DyVeriModel::DV_i_MI = "DV_In_MI";
std::string DyVeriModel::DV_o_RESULT = "DV_Out_RESULT";


DyVeriModel::DyVeriModel()
{
	SetName("DyVeriModel Model");

	// Input port
	AddInPorts(1, DV_i_LE.c_str());
	AddInPorts(1, DV_i_MI.c_str());

	// Output port
	AddOutPorts(1, DV_o_RESULT.c_str());

	// Model
	CModel *pR1Model = new CR1Model;
	AddComponent(1, pR1Model);

	CModel *pR2Model = new CR2Model;
	AddComponent(1, pR2Model);

	CModel *pR3Model = new CR3Model;
	AddComponent(1, pR3Model);

	// Coupling
	// Internal
	AddCoupling(pR1Model, CR1Model::M1_o_ES.c_str(),
		pR3Model, CR3Model::M3_i_ES.c_str());

	AddCoupling(pR2Model, CR2Model::M2_o_EL.c_str(),
		pR3Model, CR3Model::M3_i_EL.c_str());

	// External: Input to Input
	AddCoupling(this, DyVeriModel::DV_i_LE.c_str(),
		pR1Model, CR1Model::M1_i_LE.c_str());

	AddCoupling(this, DyVeriModel::DV_i_MI.c_str(),
		pR2Model, CR2Model::M2_i_MI.c_str());

	// External: Output to Output
	AddCoupling(pR3Model, CR3Model::M3_o_RESULT.c_str(),
		this, DyVeriModel::DV_o_RESULT.c_str());

	AddCoupling(pR3Model, CR3Model::M3_o_RESULT.c_str(),
		this, DyVeriModel::DV_o_RESULT.c_str());
}


DyVeriModel::~DyVeriModel()
{
}
