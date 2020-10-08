#include "gigraph/component/Draw.h"
#include "gigraph/RenderContext.h"
#include "gigraph/CompHelper.h"
#include "gigraph/ParamImpl.h"

#include <unirender/Device.h>
#include <unirender/Context.h>
#include <unirender/DrawState.h>
#include <unirender/ClearState.h>
#include <unirender/ShaderProgram.h>

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
	if (!prev_shader) {
		return;
	}

	assert(prev_shader->Type() == ParamType::Shader);
	ds.program = std::static_pointer_cast<ShaderParam>(prev_shader)->GetShader();

	auto tex_bbox_min = CompHelper::GetInputParam(*this, I_BBOX_MIN);
	if (tex_bbox_min && tex_bbox_min->Type() == ParamType::Texture) {
		rc->ur_ctx->SetTexture(ds.program->QueryTexSlot("BBoxMin"),
			std::static_pointer_cast<TextureParam>(tex_bbox_min)->GetTexture());
	}
	auto tex_bbox_max = CompHelper::GetInputParam(*this, I_BBOX_MAX);
	if (tex_bbox_max && tex_bbox_max->Type() == ParamType::Texture) {
		rc->ur_ctx->SetTexture(ds.program->QueryTexSlot("BBoxMax"),
			std::static_pointer_cast<TextureParam>(tex_bbox_max)->GetTexture());
	}
	auto tex_vertex_indices = CompHelper::GetInputParam(*this, I_VERTEX_INDICES);
	if (tex_vertex_indices && tex_vertex_indices->Type() == ParamType::Texture) {
		rc->ur_ctx->SetTexture(ds.program->QueryTexSlot("vertexIndicesTex"),
			std::static_pointer_cast<TextureParam>(tex_vertex_indices)->GetTexture());
	}
	auto tex_vertices = CompHelper::GetInputParam(*this, I_VERTICES);
	if (tex_vertices && tex_vertices->Type() == ParamType::Texture) {
		rc->ur_ctx->SetTexture(ds.program->QueryTexSlot("verticesTex"),
			std::static_pointer_cast<TextureParam>(tex_vertices)->GetTexture());
	}
	auto tex_normals = CompHelper::GetInputParam(*this, I_NORMALS);
	if (tex_normals && tex_normals->Type() == ParamType::Texture) {
		rc->ur_ctx->SetTexture(ds.program->QueryTexSlot("normalsTex"),
			std::static_pointer_cast<TextureParam>(tex_normals)->GetTexture());
	}

	auto& rs = ds.render_state;
	rs.depth_test.enabled    = false;
	rs.facet_culling.enabled = false;

	ds.vertex_array = rc->ur_dev->GetVertexArray(
		ur::Device::PrimitiveType::Quad, ur::VertexLayoutType::Pos
	);

	rc->ur_ctx->Draw(ur::PrimitiveType::TriangleStrip, ds, nullptr);
}

}
}