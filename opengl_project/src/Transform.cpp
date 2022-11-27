#include "Transform.h"

glm::mat4 Transform::GetMatrix() const
{
    return glm::translate(glm::mat4(1.0f), m_Position) *
		glm::scale(glm::mat4(1.0f), m_Scale) * 
		glm::toMat4(m_Rotation);
}

Transform::Transform() : m_Position(0.0f, 0.0f, 0.0f), m_Scale(1.0f, 1.0f, 1.0f), m_Rotation(glm::mat4(1.0f))
{
}

Transform::~Transform()
{
}

void Transform::LookAt(glm::vec3 vec)
{
    glm::vec3 dir = glm::normalize(vec);

    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);

    float dot = glm::dot(up, dir);

    if (fabs(dot - 1.0f) < 0.0001f) 
    {
        m_Rotation = glm::angleAxis(glm::pi<float>()/2.0f, right);
        return;
    }
    
    m_Rotation = glm::quatLookAt(dir, up);
}
