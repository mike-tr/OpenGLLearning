#include "component.hpp"

namespace Engine::Components {

void Componenet::onEngineUpdate(Engine &engine) {
}

void Componenet::engineUpdate(Engine &engine) {
    this->update();
    this->onEngineUpdate(engine);
}

void Componenet::update() {
}

} // namespace Engine::Components