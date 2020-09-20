#pragma once

#include "gigraph/typedef.h"

#include <vector>

namespace gigraph
{

class Evaluator
{
public:
	Evaluator() {}

	void Rebuild(const std::vector<CompPtr>& comps);

}; // Evaluator

}