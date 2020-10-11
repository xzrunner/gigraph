#pragma once

#include "gigraph/Component.h"

namespace ur { class Context; class ShaderProgram; }

namespace gigraph
{
namespace comp
{

class Scene;

class Draw : public Component
{
public:
    enum InputID
    {
        I_SCENE = 0,
        I_SHADER,

        I_MAX_NUM
    };

public:
    Draw()
        : Component(1)
    {
        m_imports = {
            {{ ParamType::Scene,  "Scene" }},
            {{ ParamType::Shader, "Shader" }},
        };
    }

    virtual void Execute(const std::shared_ptr<dag::Context>& ctx = nullptr);

private:
    void PrepareUniforms(const Scene& scene, const ur::ShaderProgram& prog);
    void PrepareTextures(ur::Context& ctx, const Scene& scene, 
        const ur::ShaderProgram& prog);

    RTTR_ENABLE(Component)

#define PARM_FILEPATH "gigraph/component/Draw.parm.h"
#include <dag/node_parms_gen.h>
#undef PARM_FILEPATH

}; // Draw

}
}
