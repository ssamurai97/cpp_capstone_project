//
// Created by kuchlong2 on 8/15/20.
//

#ifndef MY_GAME_UTIL_H
#define MY_GAME_UTIL_H
#include <GL/glew.h>
#include <csignal>
#include <fmt/core.h>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// macro for handling opengl errors
#define ASSERT(x) if (!(x)) raise(SIGTRAP)
#define GLCall(x) GLClearError(); \
  x;                              \
ASSERT(GLLogCall(#x, __FILE__, __LINE__))


/*
 * for window use
 * ------------------------------
 * ASSERT(X) if (!(x)) __debugbreak()
 * #define GLCall(x) GLClearError(); \
  x;                              \
ASSERT(GLLogCall(#x, __FILE__, __LINE__))
 */


void GLClearError();


bool GLLogCall(const char *func, const char *file, int line);


namespace my_game {


template<typename T> using Unique_ptr = std::unique_ptr<T>;

template<typename T, typename... Args> constexpr Unique_ptr<T> create_unique(Args... args)
{
  return std::make_unique<T>(std::forward<Args>(args)...);
}

template<typename T> using Shared_Ref = std::shared_ptr<T>;

template<typename T, typename... Args>

constexpr Shared_Ref<T> create_shared(Args... args)
{
  return std::make_shared<T>(std::forward<Args>(args)...);
}



inline bool near_zero(float val, float epsilon = 0.001f)
{
  if (fabs(val) <= epsilon)
  {
    return true;
  }
  else
  {
    return false;
  }
}


const float Pi = 3.1415926535f;
const float Two_pi = Pi * 2.0f;



static glm::mat4 CreateScale(float xScale, float yScale, float zScale)
{
  glm::mat4 temp =
    {
      { xScale, 0.0f, 0.0f, 0.0f },
      { 0.0f, yScale, 0.0f, 0.0f },
      { 0.0f, 0.0f, zScale, 0.0f },
      { 0.0f, 0.0f, 0.0f, 1.0f }
    };
  return glm::mat4(temp);
}

static glm::mat4 CreateScale(const glm::vec3 & scaleVector)
{
  return CreateScale(scaleVector.x, scaleVector.y, scaleVector.z);
}

// Create a scale matrix with a uniform factor
static glm::mat4 CreateScale(float scale)
{
  return CreateScale(scale, scale, scale);
}


static glm::mat4 CreateSimpleViewProj(float width, float height)
{
  glm::mat4 temp =
    {
      { 2.0f/width, 0.0f, 0.0f, 0.0f },
      { 0.0f, 2.0f/height, 0.0f, 0.0f },
      { 0.0f, 0.0f, 1.0f, 0.0f },
      { 0.0f, 0.0f, 1.0f, 1.0f }
    };
  return glm::mat4(temp);
}



static glm::mat4 CreateRotationZ(float theta)
{
  glm::mat4 temp =
    {
      { glm::cos(theta), glm::sin(theta), 0.0f, 0.0f },
      { -glm::sin(theta), glm::cos(theta), 0.0f, 0.0f },
      { 0.0f, 0.0f, 1.0f, 0.0f },
      { 0.0f, 0.0f, 0.0f, 1.0f },
    };
  return glm::mat4(temp);
}

static glm::mat4 CreateTranslation(const glm::vec3& trans)
{
   glm::mat4 temp =
    {
      { 1.0f, 0.0f, 0.0f, 0.0f },
      { 0.0f, 1.0f, 0.0f, 0.0f },
      { 0.0f, 0.0f, 1.0f, 0.0f },
      { trans.x, trans.y, trans.z, 1.0f }
    };
  return glm::mat4 (temp);
}

}
#endif
