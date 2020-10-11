/*
 * MIT License
 *
 * Copyright(c) 2019-2020 Asif Ali
 *
 * Authors/Contributors:
 *
 * Asif Ali
 * Cedric Guillemet
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this softwareand associated documentation files(the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions :
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once

#include <SM_Vector.h>

#include <vector>

namespace GLSLPT
{
    enum MaterialType
    {
        MICROFACET,
        SMOOTH_GLASS
    };

    class Material
    {
    public:
        Material()
        {
            albedo   = sm::vec3(1.0f, 1.0f, 1.0f);
            emission = sm::vec3(0.0f, 0.0f, 0.0f);

            materialType = MICROFACET;
            unused       = 0;

            metallic    = 0.0f;
            roughness   = 0.5f;
            ior         = 1.45f;
            unused2     = 0.0f;

            albedoTexID             = -1.0f;
            metallicRoughnessTexID  = -1.0f;
            normalmapTexID          = -1.0f;
            unused3                 =  0.0f;
        };

        sm::vec3 albedo;
        float materialType;
        sm::vec3 emission;

        float unused;

        float metallic;
        float roughness;
        float ior;
        float unused2;

        float albedoTexID;
        float metallicRoughnessTexID;
        float normalmapTexID;
        float unused3;
    };
}