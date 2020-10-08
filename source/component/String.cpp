#include "gigraph/component/String.h"
#include "gigraph/CompHelper.h"
#include "gigraph/Param.h"
#include "gigraph/ParamImpl.h"

namespace gigraph
{
namespace comp
{

void String::Execute(const std::shared_ptr<dag::Context>& ctx)
{
    std::string str;

    auto prev = CompHelper::GetInputParam(*this, 0);
    if (prev && prev->Type() == ParamType::String) {
        str = std::static_pointer_cast<StringParam>(prev)->GetString();
    }

    str.append(m_string);

    auto param = std::make_shared<StringParam>(str);
    m_vals = { param };
}

}
}