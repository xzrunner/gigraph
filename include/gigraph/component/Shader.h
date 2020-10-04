#pragma once

#include "gigraph/Component.h"

namespace gigraph
{
namespace comp
{

class Shader : public Component
{
public:
    Shader()
		: Component(1)
	{
		m_imports = {
			{{ ParamType::Shader, "in" }},
		};
		m_exports = {
			{{ ParamType::Shader, "out" }},
		};
	}

	virtual void Execute(const std::shared_ptr<dag::Context>& ctx = nullptr);

	RTTR_ENABLE(Component)

#define PARM_FILEPATH "gigraph/component/Shader.parm.h"
#include <dag/node_parms_gen.h>
#undef PARM_FILEPATH

}; // Shader

}
}