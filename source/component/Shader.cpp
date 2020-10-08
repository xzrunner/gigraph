#include "gigraph/component/Shader.h"
#include "gigraph/CompHelper.h"
#include "gigraph/ParamImpl.h"
#include "gigraph/RenderContext.h"

#include <unirender/Device.h>
#include <shadertrans/ShaderTrans.h>

namespace gigraph
{
namespace comp
{

void Shader::Execute(const std::shared_ptr<dag::Context>& ctx)
{
    std::string vert, frag;

    auto prev_vs = CompHelper::GetInputParam(*this, I_VS);
    if (prev_vs && prev_vs->Type() == ParamType::String) {
        vert.append(std::static_pointer_cast<StringParam>(prev_vs)->GetString());
    }

    auto prev_fs = CompHelper::GetInputParam(*this, I_FS);
    if (prev_fs && prev_fs->Type() == ParamType::String) {
        frag.append(std::static_pointer_cast<StringParam>(prev_fs)->GetString());
    }

    if (!m_vert.empty()) {
        m_vert.append(vert);
    }
    if (!m_frag.empty()) {
        m_frag.append(frag);
    }

    if (m_prog || vert.empty() || frag.empty()) {
        return;
    }

    // header
    std::string header = R"(#version 310 es
precision highp float;
precision highp int;
precision highp sampler2D;
precision highp samplerCube;
precision highp isampler2D;
precision highp sampler2DArray;
)";
    vert.insert(0, header);
    frag.insert(0, header);

    std::vector<unsigned int> vs, fs;
    shadertrans::ShaderTrans::GLSL2SpirV(shadertrans::ShaderStage::VertexShader, vert, vs);
    shadertrans::ShaderTrans::GLSL2SpirV(shadertrans::ShaderStage::PixelShader, frag, fs);
    if (vs.empty() || fs.empty()) {
        int zz = 0;
        return;
    }

    auto rc = std::dynamic_pointer_cast<RenderContext>(ctx);
    m_prog = rc->ur_dev->CreateShaderProgram(vs, fs);

    auto param = std::make_shared<ShaderParam>(m_prog);
    m_vals = { param };
}

}
}