#include "gigraph/AssetsFactory.h"

#include <PathTracer/Mesh.h>

namespace gigraph
{

CU_SINGLETON_DEFINITION(AssetsFactory);

AssetsFactory::AssetsFactory()
{
}

std::shared_ptr<GLSLPT::Mesh>
AssetsFactory::GetMesh(const std::string& filepath) const
{
	auto itr = m_meshes.find(filepath);
	if (itr != m_meshes.end()) {
		return itr->second;
	}

	auto mesh = std::make_shared<GLSLPT::Mesh>();
	if (!mesh->LoadFromFile(filepath)) {
		return nullptr;
	}

	m_meshes.insert({ filepath, mesh });

	return mesh;
}

}