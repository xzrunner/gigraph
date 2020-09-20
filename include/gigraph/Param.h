#pragma once

#include "gigraph/ParamType.h"

namespace gigraph
{

class Param
{
public:
    virtual ParamType Type() const = 0;

}; // Param

}