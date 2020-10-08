#pragma once

#include "gigraph/Component.h"

namespace gigraph
{
namespace comp
{

class Draw : public Component
{
public:
    enum InputID
    {
        I_BBOX_MIN = 0,
        I_BBOX_MAX,
        I_VERTEX_INDICES,
        I_VERTICES,
        I_NORMALS,

        I_SHADER,

        I_MAX_NUM
    };

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

            {{ ParamType::Shader,  "Shader" }},
        };
    }

    virtual void Execute(const std::shared_ptr<dag::Context>& ctx = nullptr);

    RTTR_ENABLE(Component)

#define PARM_FILEPATH "gigraph/component/Draw.parm.h"
#include <dag/node_parms_gen.h>
#undef PARM_FILEPATH

}; // Draw

}
}
