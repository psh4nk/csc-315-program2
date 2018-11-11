#include "globals.c"
// Some portions of this code were written by Dr. Pounds
/*
 * Defines the matrices necessary for
 * all transformation routines
 */

void buildReflectX(float x, float y, float z, float *pA){
    //defines the reflection matrix
    pA[ 0] = -1.0; pA[ 1] = 0.0; pA[ 2] = 0.0; pA[ 3] =   x+movex;
    pA[ 4] = 0.0; pA[ 5] = -1.0; pA[ 6] = 0.0; pA[ 7] =   y+movey;
    pA[ 8] = 0.0; pA[ 9] = 0.0; pA[10] = -1.0; pA[11] =   z+movez;
    pA[12] = 0.0; pA[13] = 0.0; pA[14] = 0.0; pA[15] = 1.0;
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

void buildTranslate( float x, float y, float z, float *pA ){
    // Constructs tranlation matrix to translate along x, y, and z axes

    pA[ 0] = 1.0; pA[ 1] = 0.0; pA[ 2] = 0.0; pA[ 3] =   x+movex;
    pA[ 4] = 0.0; pA[ 5] = 1.0; pA[ 6] = 0.0; pA[ 7] =   y+movey;
    pA[ 8] = 0.0; pA[ 9] = 0.0; pA[10] = 1.0; pA[11] =   z+movez;
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

