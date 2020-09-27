#include "Breakout.h"
#include "Level.h"

Level level;

void startGame(int *pargc, char **argv){
    //Create Game Window
    createWindow(pargc, argv);

    //Initialize level attributes
    level.initLevel();

    glutDisplayFunc(levelDisplay);
    glutMouseFunc(mouseClick);
    glutPassiveMotionFunc(mouseMove);
    glutKeyboardFunc(keyboardLinstener);

    glutMainLoop();
}

void levelDisplay() {level.displayLevel();}
void mouseClick(int button, int state, int x, int y){level.mouseClick(button, state, x, y);}
void mouseMove(int x, int y){level.mouseMove(x, y);}
void keyboardLinstener(unsigned char key, int x, int y){level.keyboardListener(key, x, y);}
