#include <stdio.h>
/* #include <OpenGL/gl.h> */
#include "glfw.h"
#include <OpenGL/glext.h>
#include <OpenGL/gl3ext.h>
#include <stdlib.h>
#include <math.h>

const double pi = 3.141592;
float t;
float univar;
GLuint uniID;

static const GLchar *vertex_shader_source= 
  {
    "attribute vec4 position;attribute vec3 normal;attribute vec4 color;varying vec4 vColor;\n"
    "uniform float uniID;varying vec3 varyingnormal;\n"
    "void main()\n"
    "{vColor = position;   gl_Position = position;}\n"
  };

static const GLchar *fragment_shader_source=
  {
    "uniform float uniID;varying vec4 vColor;\n"
    "void main()\n"
    "{ float r2 = (vColor.x+1.)*(vColor.x+1.)+(vColor.y+1.)*(vColor.y+1.);"
    "gl_FragColor = vec4((vColor.x+1.)/r2,(vColor.y+1.)/r2,uniID,1.);}\n"
  };

GLuint shader_program;
static GLboolean printShaderInfoLog(GLuint shader, const char *str);
static GLboolean printProgramInfoLog(GLuint program);

void cleateshader(){

  GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vshader,1,&vertex_shader_source, 0); /* third argument is pointer to shader source */
  glCompileShader(vshader);
  printShaderInfoLog(vshader, "vertex shader");

  GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fshader,1,&fragment_shader_source, 0); /* third argument is pointer to shader source */
  glCompileShader(fshader);
  printShaderInfoLog(fshader, "fragment shader");


  shader_program = glCreateProgram();
  glAttachShader(shader_program,vshader);
  glDeleteShader(vshader);
  glAttachShader(shader_program,fshader);
  glDeleteShader(fshader);

  glBindAttribLocation(shader_program, 0, "position");
  /* glBindFragDataLocation(shader_program, 0, "fc"); */
  glLinkProgram(shader_program);
  printProgramInfoLog(shader_program);
}

float *points;

void prepare_rectangle(){

  points = (float *)calloc(5*3,sizeof(float));

  int i;
  for(i=0;i<5;i++){
    points[3*i] = cos(360./4.*pi/180.*i);
    points[3*i+1] = sin(360./4.*pi/180.*i);
    points[3*i+2] = 0.;
  }

  for(i=0;i<5;i++){
    printf("points %d:%lf %lf %lf\n",i,points[3*i],points[3*i+1],points[3*i+2]);
  }

}

void draw_rectangle(){

  glEnableClientState(GL_VERTEX_ARRAY); 
  glVertexPointer(3, GL_FLOAT, 0, points); /* 3 float values for each vertex, offset 0*/
  glDrawArrays(GL_TRIANGLE_FAN,0,5);	     /* 5 vertices */
  glDisableClientState(GL_VERTEX_ARRAY); 
}


void rotate_triangle(){

  int i;
  for(i=0;i<4;i++){
    points[3*i] = cos(360./3.*pi/180.*i+t);
    points[3*i+1] = sin(360./3.*pi/180.*i+t);
    points[3*i+2] = 0.;
  }
  t += 1e-2;
}


GLuint myVBO_id;

void create_VBO(){

  points = (float *)calloc(4*3+1,sizeof(float));

  int i;
  for(i=0;i<4;i++){
    points[3*i] = cos(360./3.*pi/180.*i);
    points[3*i+1] = sin(360./3.*pi/180.*i);
    points[3*i+2] = 0.;
    printf("i:%d %lf %lf %lf\n",i,points[3*i],points[3*i+1],points[3*i+2]);
  }

  /* myVBO_id = 0; */
  /* glGenBuffers(1,&myVBO_id); */
  /* glBindBuffer(GL_ARRAY_BUFFER,myVBO_id); */
  /* glBufferData(GL_ARRAY_BUFFER,4*3*sizeof(float),points,GL_STATIC_DRAW); */

  /* int bufferSize = 0; */
  /* glGetBufferParameterivARB(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &bufferSize); */
  /* printf("bufferSize:%d ,4*3*sizeof(float):%lu\n",bufferSize,4*3*sizeof(float)); */


  /* glEnableClientState(GL_VERTEX_ARRAY);  // */
  /* glBindBufferARB(GL_ARRAY_BUFFER, myVBO_id);  //バインド */
  /* glVertexPointer(3, GL_FLOAT,0,0);  //最後の引数は「0」を指定 */

  /* /\* glDrawArrays(GL_TRIANGLES,0,5);  //同じ *\/ */
  /* glDrawElements(GL_TRIANGLES,5*3,GL_UNSIGNED_INT,&myVBO_id); */

  /* glDisableClientState(GL_VERTEX_ARRAY); */
  /* glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0); */
}

void draw_VBO(){

  /* glBindBuffer(GL_ARRAY_BUFFER, myVBO_id);  //バインド */

  glEnableClientState(GL_VERTEX_ARRAY); 
  glVertexPointer(3, GL_FLOAT, 0, points); /* 3 float values for each vertex, offset 0*/
  glDrawArrays(GL_TRIANGLE_FAN,0,4);	     /* 5 vertices */
  /* glDrawElements(GL_TRIANGLES,4*3,GL_UNSIGNED_INT,&myVBO_id); */
  glDisableClientState(GL_VERTEX_ARRAY); 
  /* glBindBuffer(GL_ARRAY_BUFFER, 0); */
}

int main(int argc, char **argv){

  t = 0.;

  glfwInit();

  /* glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3); */
  /* glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2); */
  /* glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); */

  glfwOpenWindow(500,500,0,0,0,0,0,0,GLFW_WINDOW);

  glfwSetWindowPos(50,100);

  glfwSetWindowTitle("playground");

  cleateshader();

  glfwSwapInterval(1);

  glClearColor(0.,0.,0.5,1.);	/* blue background */

  create_VBO();

  /* prepare_rectangle(); */

  while(glfwGetWindowParam(GLFW_OPENED)){

    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shader_program);

    univar = sin(4.*t);

    /* this is called after glUseProgram() is called. */
    uniID = glGetUniformLocation(shader_program,"uniID");
    glUniform1f(uniID,univar);

    draw_VBO();

    rotate_triangle();

    glfwSwapBuffers();
  }

  glfwTerminate();

  return 0;
}


static GLboolean printShaderInfoLog(GLuint shader, const char *str)
{
  GLint status;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
  if (status == GL_FALSE) printf("shader compile ERROR\n");
  
  GLsizei bufSize;
  glGetShaderiv(shader, GL_INFO_LOG_LENGTH , &bufSize);
  
  if (bufSize > 1)
    {
      GLchar infoLog[1024];
      GLsizei length;
      glGetShaderInfoLog(shader, bufSize, &length, infoLog);
      printf("ERROR:%s\n",infoLog);
    }
  
  return (GLboolean)status;
}

static GLboolean printProgramInfoLog(GLuint program)
{
  GLint status;
  glGetProgramiv(program, GL_LINK_STATUS, &status);
  if (status == GL_FALSE) printf("Link error\n");
  
  GLsizei bufSize;
  glGetProgramiv(program, GL_INFO_LOG_LENGTH , &bufSize);
  
  if (bufSize > 1)
  {
    GLchar infoLog[1024];
    GLsizei length;
    glGetProgramInfoLog(program, bufSize, &length, infoLog);
    fprintf(stderr,"%s",infoLog);
  }
  return (GLboolean)status;
}