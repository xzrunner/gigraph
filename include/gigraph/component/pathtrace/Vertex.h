#pragma once

#include "gigraph/component/String.h"

namespace gigraph
{
namespace comp
{
namespace pathtrace
{

class Vertex : public String
{
public:
	Vertex()
	{
        SetString(R"(
layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texCoords;

out vec2 TexCoords;

void main()
{
    gl_Position = vec4(position.x,position.y,0.0,1.0);
    TexCoords = texCoords;
}
)");
	}

	RTTR_ENABLE(String)

}; // Vertex

}
}
}