
#ifndef GAMECONFIG_H
#define GAMECONFIG_H

#define TIMER 16.6

// Screen Settings
#define WINTITLE "Breakout Game"
const int WINWIDTH  = 800;
const int WINHEIGHT = 600;

const int WALLWIDTH = 700;                     
const int WALLHEIGHT = 180;                         
const float WALLX = (WINWIDTH - WALLWIDTH) / 2.0f;  
const float WALLY = WALLX + 40;                    
const int WALLSPACE = 3;                            
const int WALLCOLS = 15;                            
const int WALLROWS = 10;                            

#endif
