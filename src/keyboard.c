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
    if(key == '+')
        DELTA_SPIN -= 100;
    if(key == '-')
        DELTA_SPIN += 100;
    if(key == 'f' || key == 'F')
        fillTree();
    if(key == 's' || key == 'S') 
        stopAnimation();
    if(key == 'i' || key == 'I')
        stopAndReset();
    //if(key == 't' || key == 'T'){ 
        //tessellate();
    //}
}

