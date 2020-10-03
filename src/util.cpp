//
// utility file
//

#include "../include/util.h"
void GLClearError()
{
  while (glGetError() != GL_NO_ERROR)
    ;
}


bool GLLogCall(const char *func, const char *file, int line)
{
  while (GLenum error = glGetError()) {
    fmt::print("[OpenGl Error] {} \n function: {} \n file: {}\n line number: {} \n ", error, func, file, line);
    return false;
  }
  return true;
}

