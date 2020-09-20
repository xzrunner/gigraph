#pragma once

#include "gigraph/typedef.h"

namespace gigraph
{

class CompHelper
{
public:
    static CompPtr GetInputComp(const Component& comp, size_t idx);
    static ParamPtr  GetInputParam(const Component& comp, size_t idx);

}; // CompHelper

}