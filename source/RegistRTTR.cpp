#include "gigraph/Component.h"
//#include "gigraph/Param.h"

#define EXE_FILEPATH "gigraph/node_include_gen.h"
#include "gigraph/node_regist_cfg.h"
#undef EXE_FILEPATH

#include <rttr/registration>

#define REGIST_NODE_TYPE(type, name)                                       \
	rttr::registration::class_<gigraph::component::type>("gigraph::"#name) \
		.constructor<>()                                                   \
	;

#define REGIST_ENUM_ITEM(type, name, label) \
    rttr::value(name, type),                \
    rttr::metadata(type, label)             \


RTTR_REGISTRATION
{

rttr::registration::class_<dag::Node<gigraph::ParamType>::Port>("gigraph::Node::Port")
	.property("var", &dag::Node<gigraph::ParamType>::Port::var)
;

rttr::registration::class_<gigraph::Component>("gigraph::Component")
	.method("GetImports", &gigraph::Component::GetImports)
	.method("GetExports", &gigraph::Component::GetExports)
;

#define EXE_FILEPATH "gigraph/node_rttr_gen.h"
#include "gigraph/node_regist_cfg.h"
#undef EXE_FILEPATH

}

namespace gigraph
{

void regist_rttr()
{
}

}