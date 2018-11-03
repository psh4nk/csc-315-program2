#include <cmath>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <vector>

typedef struct vertex {
    float x;
    float y;
    float z;
    float w;
} vertex;

int count = 0;
std::vector<vertex> tree;

/* Define these two variables to have a global scope */
float DELTA_SPIN = 0.0;
float SPIN  = 0.0;

// scaling variables
float scalex = 1.0, scaley = 1.0, scalez = 1.0;

// moving variables (arrow keys)
float movex = 0.0, movey = 0.0, movez = 0.0;

//flag to handle reflection
int reflectflag = 0;

