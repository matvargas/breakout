#include "Level.h"

using namespace std;

void recomputeFrame(int value);

Level::Level(){
    initLevel();
}

Level::~Level(){}

void Level::initLevel(void){
    ballCount = MAXBALLS;
    balls.clear();
    bricks.clear();
    initPaddle();
    initBricks();
}

void Level::displayLevel(void) {

    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);
    glOrtho(0.0f, WINWIDTH, WINHEIGHT, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    drawBackground();
    drawBallCount();

    drawPaddle();
    drawBalls();
    drawBricks();

    glutTimerFunc(TIMER, recomputeFrame, 0);
    
    glutSwapBuffers();
}

void recomputeFrame(int value) {
	glutPostRedisplay();
}

void Level::initPaddle(void) {
    paddle.r = 255.0f;
    paddle.g = 255.0f;
    paddle.b = 255.0f;
    paddle.width = 150.0f;
    paddle.height = 12.0f;
    paddle.xpos = WINWIDTH / 2.0f - paddle.width / 2.0f;
    paddle.ypos = WINHEIGHT - 20.0f;
}

void Level::drawPaddle() {
    glColor3f(paddle.r, paddle.g, paddle.b);
    glRectf(paddle.xpos + 10.0f, paddle.ypos, paddle.xpos + paddle.width - 10.0f, paddle.ypos + paddle.height);
}

void Level::newBall(float x = -1, float y = -1) {
    Ball b1;
    if (x < 0 || y < 0) {
        b1.xpos = WINWIDTH / 2.0;
        b1.ypos = WINHEIGHT - 30.0f;
    } else {
        b1.xpos = x;
        b1.ypos = y;
    }
    if ((float) rand() / (RAND_MAX) < 0.5)
        b1.xvel = 5.0f;
    else
        b1.xvel = -5.0f;
    b1.yvel = -10.0f;
    b1.radius = 6.0f;
    b1.r = 0.4f + (float) rand() / (RAND_MAX);
    b1.g = 0.25f + (float) rand() / (RAND_MAX);
    b1.b = 0.4f + (float) rand() / (RAND_MAX);
    balls.push_back(b1);
}

void Level::ballHandler(void){
    newBall(paddle.xpos + paddle.width/2, WINHEIGHT - 30.0f);
}

void Level::drawBalls(void) {
    for (std::vector<Ball>::iterator it = balls.begin(); it != balls.end(); ) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glBegin(GL_POLYGON);
        glColor3f(it->r, it->g, it->b);
        for(int j = 0; j < 50; j++) {
            float const theta = 2.0f * 3.1415926f * (float)j / (float)50;
            float const x = it->radius * cosf(theta);
            float const y = it->radius * sinf(theta);
            glVertex2f(x + it->xpos, y + it->ypos);
        }
        glEnd();

        //TODO: Allow user pause the game
        // if(pausedGame){
        //     continue;
        // }

        it->xpos += it->xvel;
        it->ypos += it->yvel;
        
        if ( (it->xpos <= (2 * it->radius)) || (it ->xpos >= (WINWIDTH - 2 * it->radius)) ) {
            it->xvel *= -1;
        }
        if ( (it->ypos <= (2 * it->radius)) ) {
            it->yvel *= -1;
        }
        if (it->ypos >= (WINHEIGHT - 2 * it->radius)) {
            it = balls.erase(it);
            ballCount --;
            if(ballCount == 0)
                exit(EXIT_SUCCESS);
            continue;
        }
        
        for (std::vector<Brick>::iterator br = bricks.begin(); br != bricks.end(); ) {
            if (it->ypos >= br->ypos && it->ypos <= br->ypos + br->height) {
                if ((it->xpos - it->radius - br->xpos - br->width) <= 5 && (it->xpos - it->radius - br->xpos - br->width) >= 0) {
                    it->xvel *= -1;
                    br = hitBrick(br);
                    continue;
                }
                
                if ((it->xpos + it->radius - br->xpos) >= -5 && (it->xpos + it->radius - br->xpos) <= 0) {
                    it->xvel *= -1;
                    br = hitBrick(br);
                    continue;
                }
            }
            
            if (it->xpos >= br->xpos && it->xpos <= br->xpos + br->width) {
                if ((it->ypos - it->radius - br->ypos - br->height) <= 10 && (it->ypos - it->radius - br->ypos - br->height) >= 0) {
                    it->yvel *= -1;
                    br = hitBrick(br);
                    continue;
                }
                
                if ((it->ypos + it->radius - br->ypos) >= -10 && (it->ypos + it->radius - br->ypos) <= 0) {
                    it->yvel *= -1;
                    br = hitBrick(br);
                    continue;
                }
            }
            
            GLfloat d;
            d = pow((it->xpos - br->xpos), 2.0) + pow((it->ypos - br->ypos), 2.0);
            if (d < it->radius + 5.0) {
                it->xvel *= -1;
                it->yvel *= -1;
                br = hitBrick(br);
                continue;
            }

            d = pow((it->xpos - br->xpos - br->width), 2.0) + pow((it->ypos - br->ypos), 2.0);
            if (d < it->radius + 5.0) {
                it->xvel *= -1;
                it->yvel *= -1;
                br = hitBrick(br);
                continue;
            }

            d = pow((it->xpos - br->xpos), 2.0) + pow((it->ypos - br->ypos - br->height), 2.0);
            if (d < it->radius + 5.0) {
                it->xvel *= -1;
                it->yvel *= -1;
                br = hitBrick(br);
                continue;
            }
            
            d = pow((it->xpos - br->xpos - br->width), 2.0) + pow((it->ypos - br->ypos - br->height), 2.0);
            if (d < it->radius + 5.0) {
                it->xvel *= -1;
                it->yvel *= -1;
                br = hitBrick(br);
                continue;
            }
            
            ++br;
        }

        if(bricks.size() <= 0){
            exit(EXIT_SUCCESS);
        }

        if (it->xpos >= paddle.xpos && it->xpos <= paddle.xpos + paddle.width) {
            if ((it->ypos + it->radius - paddle.ypos) >= -10 && (it->ypos + it->radius - paddle.ypos) <= 0) {
                it->yvel *= -1;
                continue;
            }
        }
        
        ++it;
    }
}

void Level::drawBricks(void) {
    for (std::vector<Brick>::iterator it = bricks.begin(); it != bricks.end(); ++it) {
        glColor3f(it->r, it->g, it->b);
        glRectf(it->xpos, it->ypos, it->xpos + it->width, it->ypos + it->height);
    }
}

template <typename Iterator>
Iterator Level::hitBrick(Iterator brick) {
    return bricks.erase(brick);
}

void Level::initBricks(void) {
    Brick newBrick;
    newBrick.r = 0.95f;
    newBrick.g = 0.95f;
    newBrick.b = 0.95f;
    newBrick.health = 1;
    newBrick.width = (WALLWIDTH - (WALLCOLS - 2) * WALLSPACE) / WALLCOLS;
    newBrick.height = (WALLHEIGHT - (WALLROWS - 2) * WALLSPACE) / WALLROWS;
    
    for (int i = 0; i < WALLROWS; ++i) {
        for (int j = 0; j < WALLCOLS; ++j) {
            newBrick.xpos = WALLX + j * newBrick.width + j * WALLSPACE;
            newBrick.ypos = WALLY + i * newBrick.height + i * WALLSPACE;
            bricks.push_back(newBrick);
        }
    }
}

void Level::drawBackground(void) {
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(WINWIDTH, WINHEIGHT);
    glVertex2f(-WINWIDTH, WINHEIGHT);
    glEnd();
}

void Level::drawBallCount(void) {
    glPushMatrix();
    glColor3f(1.0f, 0.7f, 0.7f);
    glRasterPos2f(WINWIDTH - 120, 20);
    char buf[300], *p;
    p = buf;
    sprintf(buf, "Balls: ");
    do glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p); while(*(++p));
    p = buf;
    sprintf(buf, "           %d", ballCount);
    glColor3f(1.0f, 0.2f, 0.2f);
    glRasterPos2f(WINWIDTH - 120, 20);
    do glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p); while(*(++p));
    glPopMatrix();
}

void Level::mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if(pausedGame)
            pausedGame = false;
        else
            pausedGame = true;
    }
}

void Level::mouseMove(int x, int y) {
    y = WINHEIGHT - y;
    if (x - paddle.width / 2.0f >= 0 && x + paddle.width / 2.0f <= WINWIDTH) {
        paddle.xpos = x - paddle.width / 2.0f;
    } else if (x - paddle.width / 2.0f <= 0) {
        paddle.xpos = 0;
    } else if (x + paddle.width / 2.0f >= WINWIDTH) {
        paddle.xpos = WINWIDTH - paddle.width;
    }
}


void Level::keyboardListener(unsigned char key, int x, int y) {
    switch (key) {
        case 'q':
            exit(0);
            break;
        case 'r':
            if(restartGame){
                initLevel();
                restartGame = false;
            } else {
                initPaddle();
            }
            ballHandler();
            break;
        default:
            break;
    }
}
