#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include <string>
#include <glm/glm.hpp>
#include "shader.h"

class PointLight
{
public:
    PointLight(glm::vec3 position ,glm::vec3 color ,float power );
    void Bine(Shader shader);
    void UnBind();
private :
    glm::vec3 m_position;
    glm::vec3 m_color;
    float m_power;
};

#endif // POINTLIGHT_H
