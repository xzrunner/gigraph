#pragma once

#include "gigraph/Component.h"

namespace gigraph
{
namespace comp
{

class Draw : public Component
{
public:
    Draw()
        : Component(1)
    {
        m_imports = {
            {{ ParamType::Texture, "BBoxMin" }},
            {{ ParamType::Texture, "BBoxMax" }},
            {{ ParamType::Texture, "VertexIndices" }},
            {{ ParamType::Texture, "Vertices" }},
            {{ ParamType::Texture, "Normals" }},
        };
    }

    RTTR_ENABLE(Component)

#define PARM_FILEPATH "gigraph/component/Draw.parm.h"
#include <dag/node_parms_gen.h>
#undef PARM_FILEPATH

}; // Draw

}
}
