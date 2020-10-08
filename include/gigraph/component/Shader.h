#pragma once

#include "gigraph/Component.h"

namespace ur { class ShaderProgram; }

namespace gigraph
{
namespace comp
{

class Shader : public Component
{
public:
	enum InputID
	{
		I_VS = 0,
		I_FS,

		I_MAX_NUM
	};

public:
    Shader()
		: Component(1)
	{
		m_imports = {
			{{ ParamType::String, "vs" }},
			{{ ParamType::String, "fs" }},
		};
		m_exports = {
			{{ ParamType::Shader, "shader" }},
		};
	}

	virtual void Execute(const std::shared_ptr<dag::Context>& ctx = nullptr);

private:
	std::shared_ptr<ur::ShaderProgram> m_prog = nullptr;

	RTTR_ENABLE(Component)

#define PARM_FILEPATH "gigraph/component/Shader.parm.h"
#include <dag/node_parms_gen.h>
#undef PARM_FILEPATH

}; // Shader

}
}