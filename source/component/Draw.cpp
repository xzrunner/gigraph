#include "gigraph/component/Draw.h"
#include "gigraph/component/Scene.h"
#include "gigraph/RenderContext.h"
#include "gigraph/CompHelper.h"
#include "gigraph/ParamImpl.h"

#include <unirender/Device.h>
#include <unirender/Context.h>
#include <unirender/DrawState.h>
#include <unirender/ClearState.h>
#include <unirender/ShaderProgram.h>
#include <unirender/Uniform.h>

namespace gigraph
{
namespace comp
{

void Draw::Execute(const std::shared_ptr<dag::Context>& ctx)
{
	auto rc = std::dynamic_pointer_cast<RenderContext>(ctx);
	assert(rc);

	ur::DrawState ds = rc->ur_ds;

	auto prev_shader = CompHelper::GetInputParam(*this, I_SHADER);
	auto prev_scene  = CompHelper::GetInputParam(*this, I_SCENE);
	if (!prev_shader || !prev_scene) {
		return;
	}

	assert(prev_shader->Type() == ParamType::Shader);
	ds.program = std::static_pointer_cast<ShaderParam>(prev_shader)->GetShader();

	assert(prev_scene->Type() == ParamType::Scene);
	auto scene = std::static_pointer_cast<SceneParam>(prev_scene)->GetScene();

	PrepareUniforms(*scene, *ds.program);
	PrepareTextures(*rc->ur_ctx, *scene, *ds.program);

	auto& rs = ds.render_state;
	rs.depth_test.enabled    = false;
	rs.facet_culling.enabled = false;

	ds.vertex_array = rc->ur_dev->GetVertexArray(
		ur::Device::PrimitiveType::Quad, ur::VertexLayoutType::Pos
	);

	rc->ur_ctx->Draw(ur::PrimitiveType::TriangleStrip, ds, nullptr);
}

void Draw::PrepareUniforms(const Scene& scene, const ur::ShaderProgram& prog)
{
    auto u_hdr_res = prog.QueryUniform("hdrResolution");
    assert(u_hdr_res);
    float res = 0;
    u_hdr_res->SetValue(&res);

    auto u_top_bvh_idx = prog.QueryUniform("topBVHIndex");
    assert(u_top_bvh_idx);
    u_top_bvh_idx->SetValue(&scene.GetBvhTranslator().topLevelIndexPackedXY);

	auto u_vert_idx_sz = prog.QueryUniform("vertIndicesSize");
	assert(u_vert_idx_sz);
	u_vert_idx_sz->SetValue(&scene.GetIndicesTexWidth());

	// todo
	sm::vec2 screen_sz(400, 400);

	auto u_screen_res = prog.QueryUniform("screenResolution");
	assert(u_screen_res);
	u_screen_res->SetValue(screen_sz.xy, 2);

	auto u_num_of_lights = prog.QueryUniform("numOfLights");
	assert(u_num_of_lights);
	int lights_num = scene.GetLightsNum();
	u_num_of_lights->SetValue(&lights_num);

	//// todo
	//sm::vec2 tile_sz(100, 100);

	//auto u_inv_num_tiles_x = prog.QueryUniform("invNumTilesX");
	//assert(u_inv_num_tiles_x);
	//float inv_num_tiles_x = 1.0f / (screen_sz.x / tile_sz.x);
	//u_inv_num_tiles_x->SetValue(&inv_num_tiles_x);

	//auto u_inv_num_tiles_y = prog.QueryUniform("invNumTilesY");
	//assert(u_inv_num_tiles_y);
	//float inv_num_tiles_y = 1.0f / (screen_sz.y / tile_sz.y);
	//u_inv_num_tiles_y->SetValue(&inv_num_tiles_y);

	auto u_max_depth = prog.QueryUniform("maxDepth");
	assert(u_max_depth);
	int max_depth = 2;
	u_max_depth->SetValue(&max_depth);
}

void Draw::PrepareTextures(ur::Context& ctx, const Scene& scene, 
	                       const ur::ShaderProgram& prog)
{
	auto tex_bvh = scene.GetValue(Scene::O_BVH);
	if (tex_bvh && tex_bvh->Type() == ParamType::Texture) {
		ctx.SetTexture(prog.QueryTexSlot("BVH"),
			std::static_pointer_cast<TextureParam>(tex_bvh)->GetTexture());
	}
	auto tex_bbox_min = scene.GetValue(Scene::O_BBoxMin);
	if (tex_bbox_min && tex_bbox_min->Type() == ParamType::Texture) {
		ctx.SetTexture(prog.QueryTexSlot("BBoxMin"),
			std::static_pointer_cast<TextureParam>(tex_bbox_min)->GetTexture());
	}
	auto tex_bbox_max = scene.GetValue(Scene::O_BBoxMax);
	if (tex_bbox_max && tex_bbox_max->Type() == ParamType::Texture) {
		ctx.SetTexture(prog.QueryTexSlot("BBoxMax"),
			std::static_pointer_cast<TextureParam>(tex_bbox_max)->GetTexture());
	}
	auto tex_vertex_indices = scene.GetValue(Scene::O_VertexIndices);
	if (tex_vertex_indices && tex_vertex_indices->Type() == ParamType::Texture) {
		ctx.SetTexture(prog.QueryTexSlot("vertexIndicesTex"),
			std::static_pointer_cast<TextureParam>(tex_vertex_indices)->GetTexture());
	}
	auto tex_vertices = scene.GetValue(Scene::O_Vertices);
	if (tex_vertices && tex_vertices->Type() == ParamType::Texture) {
		ctx.SetTexture(prog.QueryTexSlot("verticesTex"),
			std::static_pointer_cast<TextureParam>(tex_vertices)->GetTexture());
	}
	auto tex_normals = scene.GetValue(Scene::O_Normals);
	if (tex_normals && tex_normals->Type() == ParamType::Texture) {
		ctx.SetTexture(prog.QueryTexSlot("normalsTex"),
			std::static_pointer_cast<TextureParam>(tex_normals)->GetTexture());
	}
	auto tex_materials = scene.GetValue(Scene::O_Materials);
	if (tex_materials && tex_materials->Type() == ParamType::Texture) {
		ctx.SetTexture(prog.QueryTexSlot("materialsTex"),
			std::static_pointer_cast<TextureParam>(tex_materials)->GetTexture());
	}
	auto tex_transforms = scene.GetValue(Scene::O_Transforms);
	if (tex_transforms && tex_transforms->Type() == ParamType::Texture) {
		ctx.SetTexture(prog.QueryTexSlot("transformsTex"),
			std::static_pointer_cast<TextureParam>(tex_transforms)->GetTexture());
	}
	auto tex_lights = scene.GetValue(Scene::O_Lights);
	if (tex_lights && tex_lights->Type() == ParamType::Texture) {
		ctx.SetTexture(prog.QueryTexSlot("lightsTex"),
			std::static_pointer_cast<TextureParam>(tex_lights)->GetTexture());
	}
}

}
}