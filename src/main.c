#include <stdio.h>
#include "fire_simulation.h"

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(1300, 720);
    glutCreateWindow("Fogo");
    glutDisplayFunc(renderScene);
    glutReshapeFunc(framebuffer_size_callback);
    glutTimerFunc(10, timerFunction, 1);

    setup();

    glutMainLoop();

    return 0;
}