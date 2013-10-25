#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

/* display bluecolor background */

void display(){

  /* do nothing */
}

int main(int argc, char **argv){

  glutInit(&argc, argv);	

  glutInitDisplayMode(GLUT_RGBA);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);

  glClearColor(0.,0.,1.,1.);	/* background color */
  glClear(GL_COLOR_BUFFER_BIT);	/* clear color buffer */
  glFlush();			/* execute openGL commands */

  glutMainLoop();

  return 0;
}
