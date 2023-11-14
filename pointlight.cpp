#include "pointlight.h"

PointLight::PointLight(glm::vec3 position ,glm::vec3 color ,float power)
    :m_position(position), m_color(color),m_power(power)
{

}

void PointLight::Bind(Shader *shader)
{
    shader->setUniform3fv("PointLightPosition", m_position);
    shader->setUniform3fv("PointLightColor", m_color);
    shader->setUniform1f("PointLightPower", m_power);
}
