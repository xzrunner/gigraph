#ifndef EXE_FILEPATH
#error "You must define EXE_FILEPATH macro before include this file"
#endif

#undef NO_PARM_FILEPATH

// object

#define PARM_NODE_TYPE Mesh
#define PARM_NODE_NAME mesh
#include EXE_FILEPATH

#define PARM_NODE_TYPE Material
#define PARM_NODE_NAME material
#include EXE_FILEPATH

// operator

#define PARM_NODE_TYPE Transform
#define PARM_NODE_NAME transform
#include EXE_FILEPATH

// render

#define PARM_NODE_TYPE Draw
#define PARM_NODE_NAME draw
#include EXE_FILEPATH

// tool

#define PARM_NODE_TYPE Scene
#define PARM_NODE_NAME scene
#include EXE_FILEPATH
