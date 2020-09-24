#include "Screen.h"

void createWindow(int *pargc, char **argv){
    glutInit(pargc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_MULTISAMPLE);
    glutInitWindowSize(WINWIDTH, WINHEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(WINTITLE);
}