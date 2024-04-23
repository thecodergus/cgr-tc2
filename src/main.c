#include <stdio.h>
#include "fire_simulation.h"

int main(int argc, char **argv)
{
    printf("Ola Mundo\n");

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Doom Fire");
    glutDisplayFunc(renderScene);
    glutReshapeFunc(framebuffer_size_callback);
    glutTimerFunc(10, timerFunction, 1);

    setup();

    glutMainLoop();

    return 0;
}