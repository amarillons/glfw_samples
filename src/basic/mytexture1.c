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
    "attribute vec3 myatr;\n"
    "uniform float uniID;varying vec3 varyingnormal;uniform vec3 uniform2;\n"
    "varying float myvarying;\n"
    "void main()\n"
    "{gl_FrontColor = gl_Color;vColor = position;   gl_Position = position; vColor = vec4(myatr,1.);"
    "myvarying = min(position.y+0.5,1.);"
    "gl_Position.x += 0.0;"
    "}\n"
  };

static const GLchar *fragment_shader_source=
  {
    "uniform float uniID;varying vec4 vColor;uniform vec3 uniform2;\n"
    "varying float myvarying;\n"
    "void main()\n"
    "{ float r2 = (vColor.x+1.)*(vColor.x+1.)+(vColor.y+1.)*(vColor.y+1.);"
    "vec4 v_mine = vec4(uniform2,1.);\n"
    /* "gl_FragColor = vec4((vColor.x+1.)/r2,(vColor.y+1.)/r2,uniID,1.);}\n" */
    /* "myvarying += 0.1;"     */
    "gl_FragColor = vec4(gl_Color.x*myvarying,gl_Color.y*myvarying,gl_Color.z*myvarying,1.);\n"
    "if(step(uniform2.x,fract(gl_Color.x*20.))!=1. || step(uniform2.x,fract(gl_Color.y*20.))!=1.) gl_FragColor = gl_Color.grba;"
    /* "gl_FragColor = v_mine;}\n" */
    /* "gl_FragColor = vec4(1.,0.,0.,1.);" */
    "}\n"
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


void time_evolution_triangle(){

  int i;
  for(i=0;i<4;i++){
    points[6*i] = cos(360./3.*pi/180.*i+t);
    points[6*i+1] = sin(360./3.*pi/180.*i+t);
    points[6*i+2] = 0.;
    switch(i%3){
    case 1:			/* vertex 1/3 of a triangle. */
      points[6*i+3] = 1;	/* to color vertex array */
      points[6*i+4] = 0;
      points[6*i+5] = 0;
      break;
    case 2:			/* vertex 2/3 of a triangle. */
      points[6*i+3] = 0;
      points[6*i+4] = 1;
      points[6*i+5] = 0;
      break;
    default:			/* vertex 3/3 of a triangle. */
      points[6*i+3] = 0;
      points[6*i+4] = 0;
      points[6*i+5] = 1;
      break;
    }
  }
  t += 1e-2;
}


void rotate_triangle(){

  int i;
  for(i=0;i<4;i++){
    points[3*i] = cos(360./3.*pi/180.*i+t);
    points[3*i+1] = sin(360./3.*pi/180.*i+t)+sin(t);
    points[3*i+2] = sin(t);
  }
  t += 1e-2;
}


GLuint myVBO_id;

void create_VBO(){

  points = (float *)calloc(4*6+1,sizeof(float));

  int i;
  for(i=0;i<4;i++){
    points[6*i] = cos(360./3.*pi/180.*i);
    points[6*i+1] = sin(360./3.*pi/180.*i);
    points[6*i+2] = 0.;
    points[6*i+3] = 0.;
    points[6*i+4] = 1.;
    points[6*i+5] = 0.;
    printf("points[%d]: %lf %lf %lf\n",i,points[6*i],points[6*i+1],points[6*i+2]);
  }

}

void draw_VBO(){

  glBindBuffer(GL_ARRAY_BUFFER, myVBO_id);  //バインド

  glEnableClientState(GL_VERTEX_ARRAY); 
  glEnableClientState(GL_COLOR_ARRAY); 
  glVertexPointer(3, GL_FLOAT, 6*sizeof(float), points); /* 3 float values for each vertex, offset 0*/
  glColorPointer(3, GL_FLOAT, 6*sizeof(float), &points[3]); /* 3 float values for each vertex, offset 0*/

  glDrawArrays(GL_TRIANGLE_FAN,0,4);	     /* 5 vertices */
  /* glDrawElements(GL_TRIANGLES,4*3,GL_UNSIGNED_INT,&myVBO_id); */
  glDisableClientState(GL_COLOR_ARRAY); 
  glDisableClientState(GL_VERTEX_ARRAY); 
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

int main(int argc, char **argv){

  t = 0.;

  glfwInit();

  /* glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3); */
  /* glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2); */
  /* glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); */

  glfwOpenWindow(500,500,0,0,0,0,0,0,GLFW_WINDOW);

  glfwSetWindowPos(50,100);

  glfwSetWindowTitle("halfshadow triangle");

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

    glUniform3f(glGetUniformLocation(shader_program,"uniform2"),sin(3.*t),sin(t),cos(t));
    int index = glGetAttribLocation(shader_program,"myatr");

    glVertexAttrib3f(index,1.,0.,0.);

    time_evolution_triangle();

    draw_VBO();

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
