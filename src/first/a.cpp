#include <iostream>
#include "../basic/glfw3.h"
#include <OpenGL/glext.h>
#include <OpenGL/gl3ext.h>
#include <stdlib.h>
#include <math.h>

struct Rendering{
  virtual void initialize(int width, int height) = 0;
};

class RenderingClass : public Rendering{
public:
  RenderingClass();
  void initialize(int width, int height);
private:
  GLuint BuildShader(const char* source, GLenum shaderType) const;
  GLuint BuildProgram(const char* vertexShader, const char* fragmentShader) const;
  GLuint m_shader_program;
  GLuint m_framebuffer;
  GLuint m_colorRenderbuffer;
  // static GLboolean printShaderInfoLog(GLuint shader, const char *str);
  // static GLboolean printProgramInfoLog(GLuint program);
};

RenderingClass :: RenderingClass(){

}

void RenderingClass :: initialize(int width, int height){

  BuildProgram("vs","fr");

}

RenderingClass* createRenderingClass(){

  return new RenderingClass;
}

GLuint RenderingClass :: BuildShader(const char* source, GLenum shaderType) const{


}

GLuint RenderingClass :: BuildProgram(const char* vertexShader, const char* fragmentShader) const{

  std::cout << "Building programme." << std::endl;

}

int width = 200; int height = 200;

int main(){

  glfwInit();

  // t = 0.;
  GLFWwindow* window;

  window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);

  glfwGetFramebufferSize(window, &width, &height);

  while (!glfwWindowShouldClose(window)){

    glfwSwapInterval(1);

    glClearColor(0.,0.,0.5,1.);	/* blue background */

  }

  return 0;
}
