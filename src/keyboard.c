#include "move.c"

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
        if(reflectflag == 0)
            reflectflag = 1;
        else
            reflectflag = 0;
    }
    
    // polygon spin control
    if(key == '+')
        DELTA_SPIN -= 100;
    if(key == '-')
        DELTA_SPIN += 100;

    //tesselation control
    if(key == 'f' || key == 'F')
        if(tessflag == 0)
            tessflag = 1;
        else 
            tessflag = 0;
    if(key == 't' || key == 'T'){ 
        tessellate();
        if(tessflag == 0)
            tessflag = 1;
        else 
            tessflag = 0;
    }
    
    // animation control
    if(key == 's' || key == 'S') 
        stopAnimation();
    if(key == 'i' || key == 'I')
        stopAndReset();  
}

