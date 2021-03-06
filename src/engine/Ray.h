//
//  Author: Shervin Aflatooni
//

#pragma once

#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Line.h"

class Ray
{
public:
  Ray(glm::vec3 position, glm::vec3 direction);
  ~Ray(void);

  static Ray getPickRay(glm::vec2 mousePosition, const glm::vec4 &viewport, const glm::mat4 &viewMatrix, const glm::mat4 &projectionMatrix);

  glm::vec3 getPosition(void) const;
  glm::vec3 getDirection(void) const;
  glm::vec3 getEndPosition(float length) const;

  Line getLine(float length) const;

private:
  glm::vec3 m_position;
  glm::vec3 m_direction;
};
