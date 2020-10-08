#pragma once

#include "gigraph/Component.h"

namespace gigraph
{
namespace comp
{

class String : public Component
{
public:
    String()
		: Component(1)
	{
		m_imports = {
			{{ ParamType::String, "in" }},
		};
		m_exports = {
			{{ ParamType::String, "out" }},
		};
	}

	virtual void Execute(const std::shared_ptr<dag::Context>& ctx = nullptr);

	RTTR_ENABLE(Component)

#define PARM_FILEPATH "gigraph/component/String.parm.h"
#include <dag/node_parms_gen.h>
#undef PARM_FILEPATH

}; // String

}
}