#pragma once

#include <memory>

namespace gigraph
{

class Component;
using CompPtr = std::shared_ptr<Component>;

class Param;
using ParamPtr = std::shared_ptr<Param>;

}