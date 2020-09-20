#pragma once

#include "gigraph/Component.h"

#include <SM_Vector.h>

namespace GLSLPT { class Mesh; }

namespace gigraph
{
namespace comp
{

class Mesh : public Component
{
public:
    Mesh()
        : Component(1)
    {
        m_imports = {
            {{ ParamType::Material, "Material" }},
        };
        m_exports = {
            {{ ParamType::Meshes, "Mesh" }},
        };
    }

    virtual void Execute(const std::shared_ptr<dag::Context>& ctx = nullptr);

private:
    std::shared_ptr<GLSLPT::Mesh> m_impl = nullptr;

    RTTR_ENABLE(Component)

#define PARM_FILEPATH "gigraph/component/Mesh.parm.h"
#include <dag/node_parms_gen.h>
#undef PARM_FILEPATH

}; // Mesh

}
}