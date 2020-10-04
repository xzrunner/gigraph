#include "gigraph/component/Shader.h"
#include "gigraph/CompHelper.h"
#include "gigraph/Param.h"
#include "gigraph/ParamImpl.h"

namespace gigraph
{
namespace comp
{

void Shader::Execute(const std::shared_ptr<dag::Context>& ctx)
{
    std::string str;

    auto prev = CompHelper::GetInputParam(*this, 0);
    if (prev && prev->Type() == ParamType::Shader) {
        str = std::static_pointer_cast<ShaderParam>(prev)->GetShader();
    }

    str += "\n";
    str += m_shader;

    auto param = std::make_shared<ShaderParam>(str);
    m_vals = { param };
}

}
}