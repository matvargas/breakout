# Breakout  

## Breakout game implementation using OpenGL and C++ language 

**All the tests were made on Ubuntu 20.04, no other operational systems are currently available**  

### Compile
In order to compile the files, make sure the following libs are properly installed on your system: 
* OpenGL: https://opengl.org/ 
* GLUT:  `sudo apt-get install freeglut3-dev` 

To execute the game you must execute <em>run</em> script on the root directory:  
`$ ./run.sh `

The script will use CMake to compile the .cpp and .h files on project, it will certify if all libs needed are properly installed.  
A build folder will be created when the compilation succeed.  
The game will start automatically, if it doesn't happen, you can navigate to the <em>build</em> folder and execute the command:  
`$ ./breakout `