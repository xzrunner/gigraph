#include "gigraph/GIGraph.h"

#include <cslang/Type.h>
#include <cslang/BuildInFuncs.h>

namespace gigraph
{

CU_SINGLETON_DEFINITION(GIGraph);

extern void regist_rttr();

GIGraph::GIGraph()
{
	regist_rttr();

    cslang::SetupTypeSystem();
    cslang::SetupBuildInFuncs();
}

}