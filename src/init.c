#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
//#include "constants.h"

void myinit( void ){
    /* attributes */

    glClearColor(0.0, 0.0, 0.0, 0.0); /* black background */
    glPointSize(1.0);

    /* set up viewing */

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (float) WINDOW_MAX,
            0.0, (float) WINDOW_MAX);
    glMatrixMode(GL_MODELVIEW);
}

