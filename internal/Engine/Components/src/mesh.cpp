#include "mesh.hpp"
#include "engine.hpp"

namespace Engine {
namespace Components {
Mesh::Mesh(Node::Transform &parent, unsigned int model, unsigned int numVertices, bool indexed, const Material &material) : material(material), parent(parent) {
    this->object = model;
    this->numVertices = numVertices;
    this->indexed = indexed;
}

void Mesh::draw(const Camera &camera) {
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

Mesh::~Mesh() {
}

void Mesh::update() {
}

void Mesh::onEngineUpdate(Engine &engine) {
}

} // namespace Components
} // namespace Engine