#ifndef BREAKOUT_H
#define BREAKOUT_H

#include "Screen.h"
#include "Level.h"

void levelDisplay();
void mouseClick(int button, int state, int x, int y);
void mouseMove(int x, int y);
void arrowKeys(int key, int x, int y);
void startGame(int *pargc, char **argv);
void keyboardLinstener(unsigned char key, int x, int y);

#endif