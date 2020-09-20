#include "gigraph/component/Mesh.h"
#include "gigraph/AssetsFactory.h"
#include "gigraph/ParamImpl.h"

namespace gigraph
{
namespace comp
{

void Mesh::Execute(const std::shared_ptr<dag::Context>& ctx)
{
	m_impl = AssetsFactory::Instance()->GetMesh(m_filepath);

	MeshInstance mesh_inst;
	mesh_inst.mesh = m_impl;

	auto param = std::make_shared<MultiMeshesParam>();
	param->AddMesh(mesh_inst);

	m_vals = { param };
}

}
}