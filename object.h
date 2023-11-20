#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <glm/glm.hpp>
#include "vertexbuffer.h"
#include "vertexarray.h"
#include "texture.h"
#include "uvbuffer.h"

class Object
{
public:
    Object(std::vector< glm::vec3 > vertices, std::vector< glm::vec2 > uvs, std::string texturePath);
    Object(std::string, std::string);
    ~Object();
    void Bind() const;
    void Unbind() const;
    void Draw() const;
    bool loadOBJ(const char*, std::vector<glm::vec3>&, std::vector<glm::vec2>&, std::vector<glm::vec3>&);
    VertexBuffer getNormals();
    glm::vec3 position;
    glm::vec3 rotationAngles;
    glm::mat4 getModelMatrix();
    glm::vec3 scale;

private:
    VertexBuffer *m_vb;
    UVBuffer *m_uvsb;
    Texture *m_texture;
    std::string m_path;
    VertexBuffer *m_normalsb;



};

#endif // OBJECT_H
