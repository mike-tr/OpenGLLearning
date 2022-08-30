#pragma once
#include "camera.hpp"
#include "component.hpp"
// #include "engine.hpp"
#include "material.hpp"
//#include "node.hpp"
#include "transformNode.hpp"

namespace Engine {
typedef class Engine Engine;

namespace Components {
class Mesh final : Componenet {
private:
    /* data */
    Material material;
    Node::Transform &parent;
    unsigned int object;
    unsigned int numVertices;
    bool indexed;

    void onEngineUpdate(Engine &engine) override;

public:
    void draw(const Camera &camera);
    Mesh(Node::Transform &parent, unsigned int model, unsigned int numVertices, bool indexed, const Material &material);
    ~Mesh();
    void update() override;
};
} // namespace Components
} // namespace Engine
