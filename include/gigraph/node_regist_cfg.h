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

#define PARM_NODE_TYPE Shader
#define PARM_NODE_NAME shader
#include EXE_FILEPATH

// tool

#define PARM_NODE_TYPE Scene
#define PARM_NODE_NAME scene
#include EXE_FILEPATH

#define PARM_NODE_TYPE String
#define PARM_NODE_NAME string
#include EXE_FILEPATH

// pathtrace

#define NO_PARM_FILEPATH
#define PARM_NODE_TYPE BRDF
#define PARM_NODE_NAME brdf
#define PARM_NODE_GROUP pathtrace
#include EXE_FILEPATH

#define NO_PARM_FILEPATH
#define PARM_NODE_TYPE Glass
#define PARM_NODE_NAME glass
#define PARM_NODE_GROUP pathtrace
#include EXE_FILEPATH

#define NO_PARM_FILEPATH
#define PARM_NODE_TYPE PathTrace
#define PARM_NODE_NAME pathtrace
#define PARM_NODE_GROUP pathtrace
#include EXE_FILEPATH

#define NO_PARM_FILEPATH
#define PARM_NODE_TYPE Vertex
#define PARM_NODE_NAME vertex
#define PARM_NODE_GROUP pathtrace
#include EXE_FILEPATH

#define NO_PARM_FILEPATH
#define PARM_NODE_TYPE Progressive
#define PARM_NODE_NAME progressive
#define PARM_NODE_GROUP pathtrace
#include EXE_FILEPATH