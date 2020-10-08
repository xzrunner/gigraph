#define XSTR(s) STR(s)
#define STR(s) #s

#ifndef PARM_NODE_TYPE
#error "You must define PARM_NODE_TYPE macro before include this file"
#endif

#ifndef PARM_FILEPATH_H
#ifdef PARM_NODE_GROUP
#define PARM_FILEPATH_H gigraph/component/PARM_NODE_GROUP/##PARM_NODE_TYPE##.h
#else
#define PARM_FILEPATH_H gigraph/component/##PARM_NODE_TYPE##.h
#endif // PARM_NODE_GROUP
#endif // PARM_FILEPATH_H

#ifndef NO_FILEPATH_INCLUDE
#include XSTR(PARM_FILEPATH_H)
#endif // NO_FILEPATH_INCLUDE

#undef PARM_FILEPATH_H
#undef PARM_NODE_GROUP
#undef PARM_NODE_NAME
#undef PARM_NODE_TYPE
#undef PARM_FILEPATH_PARM
