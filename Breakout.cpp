#include "Breakout.h"
#include "Level.h"

Level level;

void startGame(int *pargc, char **argv){
    //Create Game Window
    createWindow(pargc, argv);

    //Initialize level attributes
    level.initLevel();

    glutDisplayFunc(levelDisplay);

    glutMainLoop();
}

void levelDisplay() {level.displayLevel();}