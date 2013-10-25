#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>

/* 画面を表示するためだけのプログラム */

void display(){

  /* 何もしない */
}

int main(int argc, char **argv){

  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_RGBA);
  glutCreateWindow(argv[0]);

  glutDisplayFunc(display);

  glClearColor(0.,0.,1.,1.);	/* 背景色を設定する */
  glClear(GL_COLOR_BUFFER_BIT);	/* カラーバッファをクリアする */
  glFlush();			/* 未実行のOpenGLコマンドをすべて実行する */

  /* glutIdleFunc(display); */
  glutMainLoop();

  return 0;
}
