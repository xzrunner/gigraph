#pragma once

#include "gigraph/Component.h"

#include <RadeonRays/bvh.h>
#include <RadeonRays/bvh_translator.h>
#include <PathTracer/Material.h>

#include <SM_Matrix.h>

namespace GLSLPT { class Mesh; }

namespace gigraph
{

struct MeshInstance;
class MultiMeshesParam;
class RenderContext;

namespace comp
{

class Scene : public Component
{
public:
    enum OutputID
    {
        O_SCENE,

        O_BVH,
        O_BBoxMin,
        O_BBoxMax,
        O_VertexIndices,
        O_Vertices,
        O_Normals,
        O_Materials,
        O_Transforms,
        O_Lights,
    };

public:
    Scene()
        : Component(1)
    {
        m_imports = {
            {{ ParamType::Meshes, "Meshes" }},
        };
        m_exports = {
            {{ ParamType::Scene, "Scene" }},

            {{ ParamType::Texture, "BVH" }},
            {{ ParamType::Texture, "BBoxMin" }},
            {{ ParamType::Texture, "BBoxMax" }},
            {{ ParamType::Texture, "VertexIndices" }},
            {{ ParamType::Texture, "Vertices" }},
            {{ ParamType::Texture, "Normals" }},
            {{ ParamType::Texture, "Materials" }},
            {{ ParamType::Texture, "Transforms" }},
            {{ ParamType::Texture, "Lights" }},
        };

        m_scene_bvh = std::make_unique<RadeonRays::Bvh>(10.0f, 64, false);

        // todo
        GLSLPT::Material black;
        black.albedo    = sm::vec3(0.1f, 0.1f, 0.1f);
        black.roughness = 0.01f;
        black.metallic  = 1.0f;
        m_materials.push_back(black);

        Light light;
        light.type = LightType::QuadLight;
        light.position = sm::vec3(.34299999f, .54779997f, .22700010f);
        light.u = sm::vec3(.34299999f, .54779997f, .33200008f) - light.position;
        light.v = sm::vec3(.21300001f, .54779997f, .22700010f) - light.position;
        light.area = light.u.Cross(light.v).Length();
        light.emission = sm::vec3(17, 12, 4);
        m_lights.push_back(light);

        light.type = LightType::QuadLight;
        light.position = sm::vec3(-.34299999f, .54779997f, .22700010f);
        light.u = sm::vec3(-.34299999f, .54779997f, .33200008f) - light.position;
        light.v = sm::vec3(-.21300001f, .54779997f, .22700010f) - light.position;
        light.area = light.u.Cross(light.v).Length();
        light.emission = sm::vec3(17, 12, 4);
        m_lights.push_back(light);

        light.type = LightType::QuadLight;
        light.position = sm::vec3(.34299999f, -.54779997f, .22700010f);
        light.u = sm::vec3(.34299999f, -.54779997f, .33200008f) - light.position;
        light.v = sm::vec3(.21300001f, -.54779997f, .22700010f) - light.position;
        light.area = light.u.Cross(light.v).Length();
        light.emission = sm::vec3(17, 12, 4);
        m_lights.push_back(light);

        light.type = LightType::QuadLight;
        light.position = sm::vec3(.34299999f, .54779997f, -.22700010f);
        light.u = sm::vec3(.34299999f, .54779997f, -.33200008f) - light.position;
        light.v = sm::vec3(.21300001f, .54779997f, -.22700010f) - light.position;
        light.area = light.u.Cross(light.v).Length();
        light.emission = sm::vec3(17, 12, 4);
        m_lights.push_back(light);
    }

    virtual void Execute(const std::shared_ptr<dag::Context>& ctx = nullptr);

    auto& GetBvhTranslator() const { return m_bvh_translator; }
    auto& GetIndicesTexWidth() const { return m_indices_tex_width; }
    auto GetLightsNum() const { return m_lights.size(); }

private:
    void BuildBVH(const MultiMeshesParam& param);
    void BuildTextures(const RenderContext& rc);

    void CreateBLAS(const std::vector<std::shared_ptr<GLSLPT::Mesh>>& meshes);
    void CreateTLAS(const std::vector<MeshInstance>& meshes);

private:
    struct Indices
    {
        int x, y, z;
    };

    enum LightType
    {
        QuadLight,
        SphereLight
    };

    struct Light
    {
        sm::vec3 position;
        sm::vec3 emission;
        sm::vec3 u;
        sm::vec3 v;
        float radius;
        float area;
        float type;
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

    //Instances
    std::vector<GLSLPT::Material> m_materials;
    //std::vector<MeshInstance> meshInstances;
    //bool instancesModified = false;

    //Lights
    std::vector<Light> m_lights;

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
