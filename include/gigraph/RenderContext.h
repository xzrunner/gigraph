#pragma once

#include <dag/Context.h>
//#include <unirender/DrawState.h>

namespace ur { class Context; class Device; }

namespace gigraph
{

class RenderContext : public dag::Context
{
public:
    //ur::DrawState     ur_ds;
    ur::Context*      ur_ctx = nullptr;
    const ur::Device* ur_dev = nullptr;

}; // RenderContext

}