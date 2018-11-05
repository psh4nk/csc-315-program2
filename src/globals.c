#include "includes.h"

typedef struct vertex {
    float x;
    float y;
    float z;
    float w;
} vertex;

typedef struct {
    unsigned all;
    unsigned left:4;
    unsigned right:4;
    unsigned bottom:4;
    unsigned top:4;
} outcode;

typedef struct{
    // struct to hold triangle data
    double a[2], b[2], c[2];
} triangle;

/*typedef struct{
    // struct to hold vertices
    int x, y;
} coords;
*/
int count = 0;
std::vector<vertex> tree;
std::vector<triangle> triangles;

/* Define these two variables to have a global scope */
float DELTA_SPIN = 0.0;
float SPIN  = 0.0;

// scaling variables
float scalex = 1.0, scaley = 1.0, scalez = 1.0;

// moving variables (arrow keys)
float movex = 0.0, movey = 0.0, movez = 0.0;

//flag to handle reflection
int reflectflag = 0;

