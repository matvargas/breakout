#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <iostream>
#include <stdlib.h>
#include <math.h>

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

    void mouseClick(int button, int state, int x, int y);
	void mouseMove(int x, int y);

    void keyboardListener(unsigned char key, int x, int y);
    
private:
    Paddle paddle;
    std::vector <Ball> balls;
    std::vector<Brick> bricks;

    int ballCount;

    bool restartGame = true;
    bool pausedGame = true;

    void drawBackground(void);
    void drawBallCount(void);

    void drawGame(void);

    void newBall(float x, float y);
    void ballHandler(void);
    void drawBalls(void);

    void initPaddle(void);
    void drawPaddle(void);

    void initBricks(void);
    void drawBricks(void);

    template <typename Iterator>
    int wallCollision(Iterator it);

    template <typename Iterator>
    bool brickCollision(Iterator it, Iterator br);

    template <typename Iterator>
    Iterator hitBrick(Iterator brick);

};

#endif