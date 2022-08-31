#pragma once
//#include "engine.hpp"
#include "componenets.fwd.hpp"
#include "engine.fwd.hpp"
#include <vector>

namespace Engine {
// class Engine;
namespace Node {
class Node {
protected:
    friend Engine;
    Node *parent;
    Node(/* args */);
    /* data */

    std::vector<Node *> nodes;
    std::vector<Components::Componenet *> componenets;

    void engineUpdate(Engine &engine);

    virtual void onEngineUpdate(Engine &engine) {}

public:
    ~Node();
    // Called each frame
    void addNode(Node *node);
    void addComponenet(Components::Componenet *componenet);
    virtual void update();
};
} // namespace Node
} // namespace Engine
