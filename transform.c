#include "matrices.c"
#include "constants.h"

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

