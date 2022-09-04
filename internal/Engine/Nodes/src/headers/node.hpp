#pragma once
//#include "engine.hpp"
#include "componenets.fwd.hpp"
#include "engine.fwd.hpp"
#include <glm/glm.hpp>
#include <vector>

namespace Engine {
// class Engine;
namespace Node {
class Transform;
class Node {
protected:
    glm::mat4 globalTransformMatrix = glm::mat4(1.0f);
    friend Engine;
    friend Transform;
    Node *parent = nullptr;
    Node(/* args */);
    /* data */

    std::vector<Node *> nodes;
    std::vector<Components::Componenet *> componenets;

    void engineUpdate(Engine &engine);
    virtual void updateTransformMatrix(glm::mat4 const parentTransformMatrix);
    virtual void onEngineUpdate(Engine &engine) {}

public:
    ~Node();
    // Called each frame
    void addNode(Node *node);
    void addComponenet(Components::Componenet *componenet);
    virtual glm::mat4 const getTransformMatrix();
    virtual void update();
};
} // namespace Node
} // namespace Engine
