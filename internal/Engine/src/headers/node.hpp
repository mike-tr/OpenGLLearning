//#include "engine.hpp"
#pragma once
#include <list>

namespace Engine {
class Node {
private:
    friend class Engine;
    Node(/* args */);
    /* data */

    std::list<Node *> nodes;

    void engineUpdate();

public:
    ~Node();
    // Called each frame
    void addNode(Node *node);
    virtual void update();
};
} // namespace Engine
