// print the opengl version.
// based on: http://numata.designed.jp/ja/2007/07/opengl.html
// compile: gcc -Wall -Wextra -O2 -g ../print_opengl_version.c -o print_opengl_version -framework OpenGL -framework GLUT 

#include <stdio.h>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);

  glutCreateWindow("dummy window");

  printf("version={%s}\n", glGetString(GL_VERSION));
  printf("renderer={%s}\n", glGetString(GL_RENDERER));
  printf("vendor={%s}\n", glGetString(GL_VENDOR));

  return 0;
}
