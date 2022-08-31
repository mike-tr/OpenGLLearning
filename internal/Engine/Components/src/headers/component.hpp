#pragma once
//#include "engine.hpp"
#include "nodes.fwd.hpp"

namespace Engine {
class Engine;

namespace Components {
class Componenet {
protected:
    friend Engine;
    friend Node::Node;
    virtual void onEngineUpdate(Engine &engine);

    void engineUpdate(Engine &engine);

public:
    virtual void update();
};
} // namespace Components
} // namespace Engine