#pragma once

#include "gigraph/Component.h"

#include <RadeonRays/bvh.h>
#include <RadeonRays/bvh_translator.h>

#include <SM_Matrix.h>

namespace GLSLPT { class Mesh; }

namespace gigraph
{

struct MeshInstance;
class MultiMeshesParam;

namespace comp
{

class Scene : public Component
{
public:
    Scene()
        : Component(1)
    {
        m_imports = {
            {{ ParamType::Meshes, "Meshes" }},
        };
        m_exports = {
            {{ ParamType::Texture, "BBoxMin" }},
            {{ ParamType::Texture, "BBoxMax" }},
            {{ ParamType::Texture, "VertexIndices" }},
            {{ ParamType::Texture, "Vertices" }},
            {{ ParamType::Texture, "Normals" }},
        };

        m_scene_bvh = std::make_unique<RadeonRays::Bvh>(10.0f, 64, false);
    }

    virtual void Execute(const std::shared_ptr<dag::Context>& ctx = nullptr);

private:
    void BuildBVH(const MultiMeshesParam& param);
    void BuildTextures();

    void CreateBLAS(const std::vector<std::shared_ptr<GLSLPT::Mesh>>& meshes);
    void CreateTLAS(const std::vector<MeshInstance>& meshes);

private:
    struct Indices
    {
        int x, y, z;
    };

private:
    std::unique_ptr<RadeonRays::Bvh> m_scene_bvh = nullptr;

    // Scene Mesh Data 
    std::vector<Indices>  m_vert_indices;
    std::vector<sm::vec4> m_vertices_uvx; // Vertex Data + x coord of uv 
    std::vector<sm::vec4> m_normals_uvy;  // Normal Data + y coord of uv
    std::vector<sm::mat4> m_transforms;
    int m_indices_tex_width;
    int m_tri_data_tex_width;

    //Bvh
    RadeonRays::BvhTranslator m_bvh_translator; // For flattening the bvh
    RadeonRays::bbox          m_scene_bounds;

    RTTR_ENABLE(Component)

#define PARM_FILEPATH "gigraph/component/Scene.parm.h"
#include <dag/node_parms_gen.h>
#undef PARM_FILEPATH

}; // Scene

}
}
