#include "treedef.c"

void display( void ){
    int inPoints;             // The number of points in the arrow 
    float point[MAX];         // Array to hold homogenous coordinates for arrow
    float *apts;              // Pointer for point array 

    struct vertex inVertexArray[MAX/4]; /* array of vertices to hold points */
    struct vertex *invp;                /* Pointer for inVertexArray  */

    /* Make sure to initialize the pointers! */
    apts = &point[0];         // the pointer to the array of points 
    invp = &inVertexArray[0]; // the pointer to the array of vertices

    inPoints = tree.size();             // the actual number of points in the arrow

    glClear(GL_COLOR_BUFFER_BIT);  /*clear the window */

    /* Define Viewport */
    glColor3f(1.0, 1.0, 1.0);
    glRecti(VIEWPORT_MIN,VIEWPORT_MIN,VIEWPORT_MAX,VIEWPORT_MAX);

    /* Define the arrow points */
    defineTree( apts );
    glutPostRedisplay();
    /* Now start the process of rotating */
    PipeLine( apts, inPoints );
    toVertex( apts, invp, inPoints );

    glColor3f(1.0, 0.0, 0.0);

    /* Draw Scaled and Rotated Arrow */
    drawTree( invp, inPoints );
    if(tessflag == 1){
        fillTree(apts, inPoints);    
    }
    glutSwapBuffers();
}
