#define XSTR(s) STR(s)
#define STR(s) #s

#ifndef PARM_NODE_TYPE
#error "You must define PARM_NODE_TYPE macro before include this file"
#endif

#ifndef PARM_NODE_NAME
#error "You must define PARM_NODE_NAME macro before include this file"
#endif

#ifndef PARM_FILEPATH_PARM
#ifdef PARM_NODE_GROUP
#define PARM_FILEPATH_PARM gigraph/component/##PARM_NODE_GROUP##/##PARM_NODE_TYPE##.parm.h
#else
#define PARM_FILEPATH_PARM gigraph/component/##PARM_NODE_TYPE##.parm.h
#endif // PARM_NODE_GROUP
#endif

#define RTTR_NAME gigraph::##PARM_NODE_NAME

#ifdef PARM_NODE_GROUP
rttr::registration::class_<gigraph::comp::PARM_NODE_GROUP::PARM_NODE_TYPE>(XSTR(RTTR_NAME))
#else
rttr::registration::class_<gigraph::comp::PARM_NODE_TYPE>(XSTR(RTTR_NAME))
#endif // PARM_NODE_GROUP
.constructor<>()
#ifndef NO_PARM_FILEPATH
#define PARM_FILEPATH XSTR(PARM_FILEPATH_PARM)
#endif // NO_PARM_FILEPATH
#ifdef PARM_NODE_GROUP
#define PARM_NODE_CLASS gigraph::comp::##PARM_NODE_GROUP::##PARM_NODE_TYPE
#else
#define PARM_NODE_CLASS gigraph::comp::##PARM_NODE_TYPE
#endif // PARM_NODE_GROUP
#include <dag/rttr_prop_gen.h>
#undef PARM_FILEPATH
#undef PARM_NODE_CLASS
;

//#undef PARM_NODE_GROUP
#undef PARM_NODE_NAME
#undef PARM_NODE_TYPE
#undef PARM_FILEPATH_PARM
