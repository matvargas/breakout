#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>
#include "GL/glut.h"
#include "GameConfig.h"

struct Paddle {
    GLfloat xpos, ypos;
    GLfloat width, height;
    GLfloat r, g, b;
};

struct Ball {
    GLfloat xpos, ypos;
    GLfloat xvel, yvel;
    GLfloat radius;
    GLfloat r, g, b;
};

struct Brick {
    GLfloat xpos, ypos;
    GLfloat width, height;
    GLfloat r, g, b;
    GLint health;
    GLint value;
};

class Level {

public: 
    Level();
    ~Level();

    void initLevel(void);
    void displayLevel(void);
    
private:
    Paddle paddle;

    void initPaddle(void);
    void drawPaddle(void);
    void drawBackground(void);

};

#endif