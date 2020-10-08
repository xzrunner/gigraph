#pragma once

#include "gigraph/component/String.h"

namespace gigraph
{
namespace comp
{
namespace pathtrace
{

class Progressive : public String
{
public:
	Progressive()
	{
        SetString(R"(
out vec3 color;
in vec2 TexCoords;

void main(void)
{
    seed = gl_FragCoord.xy/screenResolution.xy;

    float r1 = 2.0 * rand();
    float r2 = 2.0 * rand();

    vec2 jitter;

    jitter.x = r1 < 1.0 ? sqrt(r1) - 1.0 : 1.0 - sqrt(2.0 - r1);
    jitter.y = r2 < 1.0 ? sqrt(r2) - 1.0 : 1.0 - sqrt(2.0 - r2);
    jitter /= (screenResolution * 0.5);

    float scale = tan(camera.fov * 0.5);
    vec2 d = (2.0 * TexCoords - 1.0) + jitter;
    d.y *= screenResolution.y / screenResolution.x * scale;
    d.x *= scale;
    vec3 rayDir = normalize(d.x * camera.right + d.y * camera.up + camera.forward);

    vec3 focalPoint = camera.focalDist * rayDir;
    float cam_r1 = rand() * TWO_PI; 
    float cam_r2 = rand() * camera.aperture;
    vec3 randomAperturePos = (cos(cam_r1) * camera.right + sin(cam_r1) * camera.up) * sqrt(cam_r2);
    vec3 finalRayDir = normalize(focalPoint - randomAperturePos);

    Ray ray = Ray(camera.position + randomAperturePos, finalRayDir);

    vec3 pixelColor = PathTrace(ray);

    color = pixelColor;
}
)");
	}

	RTTR_ENABLE(String)

}; // Progressive

}
}
}