#pragma once

#include "gigraph/typedef.h"

#include <vector>

namespace dag { class Context; }

namespace gigraph
{

class Evaluator
{
public:
	Evaluator() {}

	void Rebuild(const std::vector<CompPtr>& comps,
		const std::shared_ptr<dag::Context>& ctx);

}; // Evaluator

}