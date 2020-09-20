#pragma once

#include <cu/cu_macro.h>

#include <map>
#include <memory>

namespace GLSLPT { class Mesh; }

namespace gigraph
{

class AssetsFactory
{
public:
	std::shared_ptr<GLSLPT::Mesh>
		GetMesh(const std::string& filepath) const;

private:
	mutable std::map<std::string, std::shared_ptr<GLSLPT::Mesh>> m_meshes;

	CU_SINGLETON_DECLARATION(AssetsFactory)

}; // AssetsFactory

}