#pragma once

#include "gigraph/Param.h"

#include <SM_Matrix.h>
#include <unirender/typedef.h>

#include <memory>
#include <vector>

namespace GLSLPT { class Mesh; }

namespace gigraph
{

struct MateriailData
{
	sm::vec3 diffuse;
};

struct MeshInstance
{
	std::shared_ptr<GLSLPT::Mesh>  mesh     = nullptr;
	std::shared_ptr<MateriailData> material = nullptr;

	sm::mat4 transform;
};

class MultiMeshesParam : public Param
{
public:
	virtual ParamType Type() const { return ParamType::Meshes; }

	auto& GetMeshes() const { return m_meshes; }

	void AddMesh(const MeshInstance& mesh) { m_meshes.push_back(mesh); }
	
private:
	std::vector<MeshInstance> m_meshes;

}; // MultiMeshesParam

class MaterialParam : public Param
{
public:
	virtual ParamType Type() const { return ParamType::Material; }

private:
	MateriailData m_mat;

}; // MaterialParam

class TextureParam : public Param
{
public:
	TextureParam(const ur::TexturePtr& tex) : m_tex(tex) {}

	virtual ParamType Type() const { return ParamType::Texture; }

private:
	ur::TexturePtr m_tex = nullptr;

}; // TextureParam

}