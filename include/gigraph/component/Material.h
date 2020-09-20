#pragma once

#include "gigraph/Component.h"

namespace gigraph
{
namespace comp
{

class Material : public Component
{
public:
	Material()
		: Component(1)
	{
        m_exports = {
            {{ ParamType::Material, "Material" }},
        };
	}

	RTTR_ENABLE(Component)

#define PARM_FILEPATH "gigraph/component/Material.parm.h"
#include <dag/node_parms_gen.h>
#undef PARM_FILEPATH

}; // Material

}
}