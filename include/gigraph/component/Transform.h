#pragma once

#include "gigraph/Component.h"

namespace gigraph
{
namespace comp
{

class Transform : public Component
{
public:
    Transform()
        : Component(1)
    {
        m_imports = {
            {{ ParamType::Meshes, "Input" }},
        };
        m_exports = {
            {{ ParamType::Meshes, "Output" }},
        };
    }

    RTTR_ENABLE(Component)

#define PARM_FILEPATH "gigraph/component/Transform.parm.h"
#include <dag/node_parms_gen.h>
#undef PARM_FILEPATH

}; // Transform

}
}
