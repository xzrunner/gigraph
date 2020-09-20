#include "gigraph/Evaluator.h"
#include "gigraph/ParamType.h"
#include "gigraph/Component.h"

#include <dag/Graph.h>

namespace gigraph
{

void Evaluator::Rebuild(const std::vector<CompPtr>& comps)
{
	// sort

    std::vector<std::shared_ptr<dag::Node<ParamType>>> _comps(comps.size());
    for (size_t i = 0, n = comps.size(); i < n; ++i) {
        _comps[i] = comps[i];
    }
    auto orders = dag::Graph<ParamType>::TopologicalSorting(_comps);

    std::vector<CompPtr> sorted;
    sorted.resize(orders.size());
    for (size_t i = 0, n = orders.size(); i < n; ++i) {
        sorted[i] = comps[orders[i]];
    }

    // update
    for (auto& comp : sorted) {
        comp->Execute();
    }
}

}