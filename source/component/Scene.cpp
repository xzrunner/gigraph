#include "gigraph/component/Scene.h"
#include "gigraph/ParamImpl.h"
#include "gigraph/CompHelper.h"

#include <PathTracer/Mesh.h>

#include <SM_Cube.h>

namespace gigraph
{
namespace comp
{

void Scene::Execute(const std::shared_ptr<dag::Context>& ctx)
{
	auto param = CompHelper::GetInputParam(*this, 0);
    if (!param) {
        return;
    }

	assert(param->Type() == ParamType::Meshes);
    BuildBVH(*std::static_pointer_cast<MultiMeshesParam>(param));

    BuildTextures();
}

void Scene::BuildBVH(const MultiMeshesParam& param)
{
    auto& meshes_inst = param.GetMeshes();

	// unique
	std::set<std::shared_ptr<GLSLPT::Mesh>> meshes_set;
	for (auto& mesh_inst : meshes_inst) {
        meshes_set.insert(mesh_inst.mesh);
	}
    std::vector<std::shared_ptr<GLSLPT::Mesh>> meshes;
    std::copy(meshes_set.begin(), meshes_set.end(), std::back_inserter(meshes));

    CreateBLAS(meshes);
    CreateTLAS(meshes_inst);

    // Flatten BVH
    std::vector<GLSLPT::MeshInstance> mesh_instances;
    mesh_instances.reserve(meshes_inst.size());
    for (auto& mesh : meshes_inst) 
    {
        int mesh_id = -1;
        for (size_t i = 0, n = meshes.size(); i < n; ++i) {
            if (meshes[i] == mesh.mesh) {
                mesh_id = i;
                break;
            }
        }
        assert(mesh_id != -1);

        mesh_instances.push_back({ "", mesh_id, mesh.transform, -1 });
    }
    m_bvh_translator.Process(m_scene_bvh.get(), meshes, mesh_instances);

    int verticesCnt = 0;

    //Copy mesh data
    for (size_t i = 0; i < meshes.size(); i++)
    {
        // Copy indices from BVH and not from Mesh
        int numIndices = meshes[i]->bvh->GetNumIndices();
        const int * triIndices = meshes[i]->bvh->GetIndices();

        for (int j = 0; j < numIndices; j++)
        {
            int index = triIndices[j];
            int v1 = (index * 3 + 0) + verticesCnt;
            int v2 = (index * 3 + 1) + verticesCnt;
            int v3 = (index * 3 + 2) + verticesCnt;

            m_vert_indices.push_back(Indices{ v1, v2, v3 });
        }

        m_vertices_uvx.insert(m_vertices_uvx.end(), meshes[i]->verticesUVX.begin(), meshes[i]->verticesUVX.end());
        m_normals_uvy.insert(m_normals_uvy.end(), meshes[i]->normalsUVY.begin(), meshes[i]->normalsUVY.end());

        verticesCnt += meshes[i]->verticesUVX.size();
    }

    // Resize to power of 2
    m_indices_tex_width  = (int)(sqrt(m_vert_indices.size()) + 1);
    m_tri_data_tex_width = (int)(sqrt(m_vertices_uvx.size())+ 1);

    m_vert_indices.resize(m_indices_tex_width * m_indices_tex_width);
    m_vertices_uvx.resize(m_tri_data_tex_width * m_tri_data_tex_width);
    m_normals_uvy.resize(m_tri_data_tex_width * m_tri_data_tex_width);

    for (size_t i = 0; i < m_vert_indices.size(); i++)
    {
        m_vert_indices[i].x = ((m_vert_indices[i].x % m_tri_data_tex_width) << 12) | (m_vert_indices[i].x / m_tri_data_tex_width);
        m_vert_indices[i].y = ((m_vert_indices[i].y % m_tri_data_tex_width) << 12) | (m_vert_indices[i].y / m_tri_data_tex_width);
        m_vert_indices[i].z = ((m_vert_indices[i].z % m_tri_data_tex_width) << 12) | (m_vert_indices[i].z / m_tri_data_tex_width);
    }

    //Copy m_transforms
    m_transforms.resize(mesh_instances.size());
    #pragma omp parallel for
    for (size_t i = 0; i < mesh_instances.size(); i++) {
        m_transforms[i] = mesh_instances[i].transform;
    }

    ////Copy Textures
    //for (int i = 0; i < textures.size(); i++)
    //{
    //    texWidth = textures[i]->width;
    //    texHeight = textures[i]->height;
    //    int texSize = texWidth * texHeight;
    //    textureMapsArray.insert(textureMapsArray.end(), &textures[i]->texData[0], &textures[i]->texData[texSize * 3]);
    //}
}

void Scene::BuildTextures()
{
    ////Create texture for Bounding boxes
    //glGenTextures(1, &BBoxminTex);
    //glBindTexture(GL_TEXTURE_2D, BBoxminTex);
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, scene->bvhTranslator.nodeTexWidth, scene->bvhTranslator.nodeTexWidth, 0, GL_RGB, GL_FLOAT, &scene->bvhTranslator.bboxmin[0]);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    //glBindTexture(GL_TEXTURE_2D, 0);

    m_vals.resize(5);

    auto bbox_min_tex = std::make_shared<TextureParam>();
    m_vals[0] = bbox_min_tex;
}

void Scene::CreateBLAS(const std::vector<std::shared_ptr<GLSLPT::Mesh>>& meshes)
{
	#pragma omp parallel for
	for (auto& mesh : meshes) {
		mesh->BuildBVH();
	}
}

void Scene::CreateTLAS(const std::vector<MeshInstance>& meshes)
{
    std::vector<RadeonRays::bbox> bounds;
    bounds.reserve(meshes.size());

    #pragma omp parallel for
    for (auto& mesh_inst : meshes)
    {
        RadeonRays::bbox bbox = mesh_inst.mesh->bvh->Bounds();
        const sm::mat4& matrix = mesh_inst.transform;

        sm::vec3 minBound = bbox.pmin;
        sm::vec3 maxBound = bbox.pmax;

        sm::vec3 right       = sm::vec3(matrix.c[0][0], matrix.c[0][1], matrix.c[0][2]);
        sm::vec3 up          = sm::vec3(matrix.c[1][0], matrix.c[1][1], matrix.c[1][2]);
        sm::vec3 forward     = sm::vec3(matrix.c[2][0], matrix.c[2][1], matrix.c[2][2]);
        sm::vec3 translation = sm::vec3(matrix.c[3][0], matrix.c[3][1], matrix.c[3][2]);

        sm::vec3 xa = right * minBound.x;
        sm::vec3 xb = right * maxBound.x;

        sm::vec3 ya = up * minBound.y;
        sm::vec3 yb = up * maxBound.y;

        sm::vec3 za = forward * minBound.z;
        sm::vec3 zb = forward * maxBound.z;

        sm::cube cube;
        cube.Combine(xa);
        cube.Combine(xb);
        cube.Combine(ya);
        cube.Combine(yb);
        cube.Combine(za);
        cube.Combine(zb);

        RadeonRays::bbox bound;
        bound.pmin = cube.Min();
        bound.pmax = cube.Max();

        bounds.push_back(bound);
    }
    m_scene_bvh->Build(&bounds[0], bounds.size());
    m_scene_bounds = m_scene_bvh->Bounds();
}

}
}