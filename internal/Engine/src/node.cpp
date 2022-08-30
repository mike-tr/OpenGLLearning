#include "node.hpp"
#include "engine.hpp"
#include <iostream>

namespace Engine {

Node::Node(/* args */) {
    nodes.clear();
}

Node::~Node() {
    nodes.clear();
}

void Node::engineUpdate() {
    this->update();
    for (auto it = nodes.begin(); it != nodes.end(); ++it) {
        (*it)->engineUpdate();
    }
}

void Node::addNode(Node *node) {
    nodes.push_back(node);
}

void Node::update() {
    std::cout << "empty update" << std::endl;
}

} // namespace Engine