#include "gigraph/CompHelper.h"
#include "gigraph/Component.h"

namespace gigraph
{

CompPtr CompHelper::GetInputComp(const Component& comp, size_t idx)
{
    auto& imports = comp.GetImports();
    if (idx < 0 || idx >= imports.size()) {
        return nullptr;
    }

    auto& conns = imports[idx].conns;
    if (conns.empty()) {
        return nullptr;
    }

    assert(imports[idx].conns.size() == 1);
    auto in_comp = imports[idx].conns[0].node.lock();
    assert(in_comp->get_type().is_derived_from<Component>());
    return std::static_pointer_cast<Component>(in_comp);
}

ParamPtr CompHelper::GetInputParam(const Component& comp, size_t idx)
{
    auto& imports = comp.GetImports();
    if (idx < 0 || idx >= imports.size()) {
        return nullptr;
    }

    auto& conns = imports[idx].conns;
    if (conns.empty()) {
        return nullptr;
    }

    assert(imports[idx].conns.size() == 1);
    auto& conn = imports[idx].conns[0];
    auto in_comp = conn.node.lock();
    assert(in_comp->get_type().is_derived_from<Component>());
    return std::static_pointer_cast<Component>(in_comp)->GetValue(conn.idx);
}

}