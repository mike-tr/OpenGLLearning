#pragma once
//#include "engine.hpp"

namespace Engine {
class Engine;

namespace Components {
class Componenet {
protected:
    friend class Engine;
    virtual void onEngineUpdate(Engine &engine) {}

public:
    virtual void update(){};
};
} // namespace Components
} // namespace Engine