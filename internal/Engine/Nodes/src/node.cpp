#include "node.hpp"
#include "component.hpp"
#include "engine.fwd.hpp"
#include <iostream>

namespace Engine {
namespace Node {
Node::Node(/* args */) {
    nodes.clear();
}

Node::~Node() {
    nodes.clear();
}

void Node::engineUpdate(Engine &engine) {
    this->update();
    this->onEngineUpdate(engine);
    for (auto componenet : componenets) {
        componenet->engineUpdate(engine);
    }

    for (auto node : nodes) {
        node->engineUpdate(engine);
    }
}

void Node::addNode(Node *node) {
    nodes.push_back(node);
}

void Node::update() {
    // std::cout << "empty update" << std::endl;
}

void Node::addComponenet(Components::Componenet *componenet) {
    componenets.push_back(componenet);
}

} // namespace Node
} // namespace Engine