//Preston Shankle
//
//
//

#include <cmath>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <vector>

#define WINDOW_MAX 1000
#define WINDOW_MIN 0
#define VIEWPORT_MAX 900
#define VIEWPORT_MIN 100
#define MAX 500000

/* Define the vertex data type */
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
float scalex = 1.0, scaley = 1.0, scalez = 1.0;


void vmatm (int SIZE, float *pA, float *pB){
    // Matrix-vector multiplication
    // pA is a pointer to the first element of matrix A
    // pB is a pointer to the first element of vector B
    // On return, B will contain transformed coordinates

    int i, j;
    float temp[4];

    for (i=0; i<SIZE; i++)
        temp[i] = 0.0;

    for (i=0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++)
            temp[i] += *(pA+(i*SIZE+j)) * *(pB+j);

    for (i=0; i<SIZE; i++)
        *(pB+i) = temp[i];

}

void buildScale(float x, float y, float z, float *pA){
    // Constructs scaling matrix to scale along x, y, and z axes

    if(scalex >= 0){
        pA[ 0] = scalex; pA[ 1] = 0.0; pA[ 2] = 0.0; pA[ 3] =   0;
        pA[ 4] = 0.0; pA[ 5] = scaley; pA[ 6] = 0.0; pA[ 7] =   0;
        pA[ 8] = 0.0; pA[ 9] = 0.0; pA[10] = scalez; pA[11] =   0;
        pA[12] = 0.0; pA[13] = 0.0; pA[14] = 0.0; pA[15] = 1.0;
    }
    else{
        pA[ 0] = 0.0; pA[ 1] = 0.0; pA[ 2] = 0.0; pA[ 3] =   0;
        pA[ 4] = 0.0; pA[ 5] = 0.0; pA[ 6] = 0.0; pA[ 7] =   0;
        pA[ 8] = 0.0; pA[ 9] = 0.0; pA[10] = 0.0; pA[11] =   0;
        pA[12] = 0.0; pA[13] = 0.0; pA[14] = 0.0; pA[15] = 1.0;
    }
}

void buildTranslate( float x, float y, float z, float *pA )
    // Constructs tranlation matrix to translate along x, y, and z axes
{
    pA[ 0] = 1.0; pA[ 1] = 0.0; pA[ 2] = 0.0; pA[ 3] =   x;
    pA[ 4] = 0.0; pA[ 5] = 1.0; pA[ 6] = 0.0; pA[ 7] =   y;
    pA[ 8] = 0.0; pA[ 9] = 0.0; pA[10] = 1.0; pA[11] =   z;
    pA[12] = 0.0; pA[13] = 0.0; pA[14] = 0.0; pA[15] = 1.0; 
}

void buildRotateZ( float theta, float *pA ){
    // Constructs rotation matrix about Z axis

    float phi;

    // Convert degrees to radians

    phi = theta * M_PI / 180.0; 
    pA[ 0] =  cos(phi); pA[ 1] = sin(phi); pA[ 2] = 0.0; pA[ 3] = 0.0;
    pA[ 4] = -sin(phi); pA[ 5] = cos(phi); pA[ 6] = 0.0; pA[ 7] = 0.0;
    pA[ 8] = 0.0;       pA[ 9] = 0.0;      pA[10] = 1.0; pA[11] = 0.0;
    pA[12] = 0.0;       pA[13] = 0.0;      pA[14] = 0.0; pA[15] = 1.0;
}      




void applyTransformation( float *vp, int vpts, float *TM ){ 
    // Applies the given transformation matrix TM to the vector vp containing
    // all of the homegenous coordinates to define the object

    float temp[4];
    float *tmp;
    int i;

    tmp = &temp[0];

    for (i=0;i<vpts;i++)
    {
        *(tmp+0)= *(vp+(i*4)+0);
        *(tmp+1)= *(vp+(i*4)+1);
        *(tmp+2)= *(vp+(i*4)+2);
        *(tmp+3)= *(vp+(i*4)+3);
        vmatm( 4, TM, tmp );
        *(vp+(i*4)+0) = *(tmp+0); 
        *(vp+(i*4)+1) = *(tmp+1); 
        *(vp+(i*4)+2) = *(tmp+2); 
        *(vp+(i*4)+3) = *(tmp+3); 
    }
}


void PipeLine( float *vp, int vpts ){
    /*  This routine will run the graphics transformation pipeline. 
     *  It is operating on x,y,z homogenous coordinates defined in a linear
     *  array.  These are converted to vertex points later for possible
     *  clipping before final display.
     */ 

    /* Set up useful temporary variables */
    float TransformationMatrix[16];
    float *TM;

    /* Don't forget to initialize the ponter! */
    TM = &TransformationMatrix[0];

    //translate to origin
    buildTranslate( -WINDOW_MAX/2, -WINDOW_MAX/2, 0.0,  TM );
    applyTransformation( vp, vpts, TM );

    // Perform the rotation operation
    buildRotateZ( SPIN, TM );	
    applyTransformation( vp, vpts, TM );


    //Scale
    buildScale(0,0, 0.0, TM);
    applyTransformation(vp,vpts,TM);
    //translate back    

    //buildTranslate( WINDOW_MAX/2, WINDOW_MAX/2, 0.0,  TM );
    //applyTransformation( vp, vpts, TM );


    // Translate to origin  
    //buildTranslate( -WINDOW_MAX/2, -WINDOW_MAX/2, 0.0,  TM );
    //applyTransformation( vp, vpts, TM );   	
    // Perform the rotation operation
    //buildRotateZ( SPIN, TM );	
    //applyTransformation( vp, vpts, TM );
    // Translate back to point
    buildTranslate( WINDOW_MAX/2, WINDOW_MAX/2, 0.0,  TM );
    applyTransformation( vp, vpts, TM );   	   
}

void defineTree( float *apts ){

    float r = 200;
    float x,y;
    float TPI = 2 * M_PI;

    if(count == 0){
        count++;
        tree.push_back({200,600,0,1});
        tree.push_back({725,550,0,1});
        for (float i = 0.0; i <= TPI / 2; i += 0.001){
            x = (sin(i)*r)+650;
            y = (cos(i)*r)+500; 
            tree.push_back({x,y,0,1});
        }
        tree.push_back({725,450,0,1});
        tree.push_back({200,400,0,1});    
    }

    int vertmin = 0;
    for(int i = 0; i < tree.size(); i++){ 
        apts[vertmin] = tree[i].x;
        apts[vertmin+1] = tree[i].y;
        apts[vertmin+2] = tree[i].z;
        apts[vertmin+3] = tree[i].w; 
        vertmin+=4;
    }
}

void toVertex ( float *apts, struct vertex *vp, int pts ){
    int i;

    for (i=0;i<pts;i++)
    {
        (vp+i)->x = *(apts+(i*4)+0);
        (vp+i)->y = *(apts+(i*4)+1);
        (vp+i)->z = *(apts+(i*4)+2);
        (vp+i)->w = *(apts+(i+4)+3);
    }
}


void drawTree( vertex *vp, int points ){
    glBegin(GL_LINE_LOOP);
    for (int i=0;i<points;i++)
        glVertex2f( (vp+i)->x, (vp+i)->y );
    glEnd();    
}

void fillTree(){
    //tesselation goes here
    glBegin(GL_POLYGON);
    for(int i = 0; i < tree.size(); i++)
        glVertex2f(tree[i].x, tree[i].y);
    glEnd();
}


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



void display( void ){
    int inPoints;             // The number of points in the arrow 
    float point[MAX];         // Array to hold homogenous coordinates for arrow
    float *apts;              // Pointer for point array 

    struct vertex inVertexArray[MAX/4];	/* array of vertices to hold points */
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
    glutSwapBuffers();
}

void SpinDisplay(void){
    SPIN = SPIN + DELTA_SPIN;
    if (SPIN > 360.0) SPIN = SPIN - 360.0;
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    //std::cout << "x: " << x << ", y: " << y << "\n"; 
    switch (button) {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN && x < VIEWPORT_MAX && x > VIEWPORT_MIN && y < VIEWPORT_MAX && y > VIEWPORT_MIN){
                DELTA_SPIN = DELTA_SPIN - 1.0;
                glutIdleFunc(SpinDisplay);
            }
            else if(x > VIEWPORT_MAX || x < VIEWPORT_MIN || y > VIEWPORT_MAX || y < VIEWPORT_MIN){
                scalex += .05;
                scaley += .05;
                scalez += .05;
                //std::cout<<"LC: mouse outside window!\n";
                //increase scale
            }
            break;
        case GLUT_RIGHT_BUTTON:
            if (state == GLUT_DOWN && x < VIEWPORT_MAX && x > VIEWPORT_MIN && y < VIEWPORT_MAX && y > VIEWPORT_MIN){
                DELTA_SPIN = DELTA_SPIN + 1.0;
                glutIdleFunc(SpinDisplay);
            }
            else if(x > VIEWPORT_MAX || x < VIEWPORT_MIN || y > VIEWPORT_MAX || y < VIEWPORT_MIN){
                scalex -= .05;
                scaley -= .05;
                scalez -= .05;
                //std::cout << "RC: mouse outside window!\n";
                //decrease scale
            }
            break;
        default:
            break;
    }
}

void keyboard( unsigned char key, int x, int y ){ 
    if ( key == 'q' || key == 'Q') exit(0);
    if ( key == 'c' || key == 'C') {
        SPIN = 0.0;
        glutIdleFunc(display);
    }
    if ( key == 'x' || key == 'X') {
        glutIdleFunc(NULL);
    }
    if(key == 'r' || key == 'R'){
        DELTA_SPIN = 0;
    }
    if(key == '+')
        DELTA_SPIN += 100;
    if(key == '-')
        DELTA_SPIN -= 100;
    if(key == 'f' || key == 'F')
        fillTree();

}


int main(int argc, char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB); 
    glutInitWindowSize(WINDOW_MAX,WINDOW_MAX); 
    glutInitWindowPosition(0,0); 
    glutCreateWindow("The Arrow"); 
    myinit(); 
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display); 
    glutMainLoop();
}
