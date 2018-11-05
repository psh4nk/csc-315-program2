#include "clip.c"
#include "includes.h"

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

    // XY-axis reflection
    if(reflectflag == 1){
        buildReflectX(0.0,0.0,0.0,TM);
        applyTransformation(vp,vpts,TM); 
    }
  

    //Scale
    buildScale(0,0, 0.0, TM);
    applyTransformation(vp,vpts,TM);

    //CHClip(vp, vpts, 100,900,100,900,1);


    // Translate back to point
    buildTranslate( WINDOW_MAX/2, WINDOW_MAX/2, 0.0,  TM );
    applyTransformation( vp, vpts, TM );

    //checkintersection(vp, vpts);
}

