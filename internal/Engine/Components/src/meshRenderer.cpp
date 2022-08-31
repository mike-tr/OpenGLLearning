#include "meshRenderer.hpp"
#include "cameraNode.hpp"
#include "engine.hpp"
#include "transformNode.hpp"

namespace Engine {
namespace Components {
MeshRenderer::MeshRenderer(Node::Transform &parent, unsigned int model, unsigned int numVertices, bool indexed, const Material &material) : material(material), parent(parent) {
    this->object = model;
    this->numVertices = numVertices;
    this->indexed = indexed;
}

void MeshRenderer::draw(const Node::Camera &camera) {
    this->material.use();
    unsigned int shaderID = this->material.shader.ID;
    // camera.apply(shaderID);
    unsigned int transformLoc = glGetUniformLocation(shaderID, "transform");
    // glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(this->transformationMatrix));

    glBindVertexArray(this->object);
    if (indexed) {
        glDrawElements(GL_TRIANGLES, this->numVertices, GL_UNSIGNED_INT, 0);
        return;
    }
    glDrawArrays(GL_TRIANGLES, 0, this->numVertices);
}

MeshRenderer::~MeshRenderer() {
}

void MeshRenderer::update() {
}

void MeshRenderer::onEngineUpdate(Engine &engine) {
    engine.addDrawCall(*this);
}

} // namespace Components
} // namespace Engine