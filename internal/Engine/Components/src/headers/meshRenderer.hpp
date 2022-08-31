#pragma once
#define FORWARDS
#include "component.hpp"
#include "nodes.fwd.hpp"
// #include "engine.hpp"
#include "material.hpp"
//#include "node.hpp"
//#include "cameraNode.hpp"
//#include "transformNode.hpp"

namespace Engine {
class Engine;
namespace Components {
class MeshRenderer final : Componenet {
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
    void draw(const Node::Camera &camera);
    MeshRenderer(Node::Transform &parent, unsigned int model, unsigned int numVertices, bool indexed, const Material &material);
    ~MeshRenderer();
    void update() override;
};
} // namespace Components
} // namespace Engine