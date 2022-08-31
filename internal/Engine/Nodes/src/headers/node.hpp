#pragma once
//#include "engine.hpp"
//#include "engine.fwd.hpp"
#include <list>

namespace Engine {
class Engine;
namespace Node {
class Node {
protected:
    friend Engine;
    Node *parent;
    Node(/* args */);
    /* data */

    std::list<Node *> nodes;

    void engineUpdate(Engine &engine);

    virtual void onEngineUpdate(Engine &engine) {}

public:
    ~Node();
    // Called each frame
    void addNode(Node *node);
    virtual void update();
};
} // namespace Node
} // namespace Engine
