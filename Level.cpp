#include "Level.h"

using namespace std;

void recomputeFrame(int value);

Level::Level(){
    initLevel();
}

Level::~Level(){}

void Level::initLevel(void){
   initPaddle();
}

void Level::displayLevel(void) {

    // Clear buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // Set OpenGL for 2D drawing
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);
    glOrtho(0.0f, WINWIDTH, WINHEIGHT, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    drawBackground();

    
    glutTimerFunc(TIMER, recomputeFrame, 0);
    
    glutSwapBuffers();
}

void recomputeFrame(int value) {
	glutPostRedisplay();
}

void Level::initPaddle(void) {
    paddle.r = 0.2f;
    paddle.g = 0.5f;
    paddle.b = 1.0f;
    paddle.width = 150.0f;
    paddle.height = 12.0f;
    paddle.xpos = WINWIDTH / 2.0f - paddle.width / 2.0f;
    paddle.ypos = WINHEIGHT - 20.0f;
}

void Level::drawPaddle() {
    if (paddle.width < 25) {
        paddle.width = 25;
    }
    
    glColor3f(paddle.r, paddle.g, paddle.b);
    glRectf(paddle.xpos, paddle.ypos, paddle.xpos + 5.0f, paddle.ypos + paddle.height);
    glRectf(paddle.xpos + 10.0f, paddle.ypos, paddle.xpos + paddle.width - 10.0f, paddle.ypos + paddle.height);
    glRectf(paddle.xpos + paddle.width - 5.0f, paddle.ypos, paddle.xpos + paddle.width, paddle.ypos + paddle.height);
}

void Level::drawBackground(void) {
    glBegin(GL_POLYGON);
    // Top color
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(WINWIDTH, WINHEIGHT);
    glVertex2f(-WINWIDTH, WINHEIGHT);
    // Bottom color
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.0f, 0.0f);
    glEnd();

}
