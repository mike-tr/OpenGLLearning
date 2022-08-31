#pragma once
#define FORWARDS
#include "component.hpp"
// #include "engine.hpp"
#include "material.hpp"
//#include "node.hpp"
#include "transformNode.hpp"

class Camera;

namespace Engine {
class Engine;

namespace Components {
class Mesh final : Componenet {
private:
    /* data */
    Material material;
    Node::Transform &parent;
    unsigned int object;
    unsigned int numVertices;
    bool indexed;

protected:
    void onEngineUpdate(Engine &engine) override;

public:
    void draw(const Camera &camera);
    Mesh(Node::Transform &parent, unsigned int model, unsigned int numVertices, bool indexed, const Material &material);
    ~Mesh();
    void update() override;
};
} // namespace Components
} // namespace Engine
