#include "display.c"

void SpinDisplay(void){
    SPIN = SPIN + DELTA_SPIN;
    if (SPIN > 360.0) SPIN = SPIN - 360.0;
    glutPostRedisplay();
}

void stopAnimation(void){
    // Reset polygon spin speed
    DELTA_SPIN = 0.0;
}

void stopAndReset(){
    // Reset polygon spin speed, 
    // move tree back to start point,
    // reflect the tree back to original 
    // and scale back to original point
    SPIN = 0.0;
    DELTA_SPIN = 0.0;
    scalex = 1.0, scaley = 1.0, scalez = 1.0;
    movex = 0.0, movey = 0.0, movez = 0.0;
    reflectflag = 0;
    tessflag = 0;
    fillflag = 0;
}


void mouse(int button, int state, int x, int y) { 
    // Controls mouse input
    switch (button) {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN && x < VIEWPORT_MAX && x > VIEWPORT_MIN && y < VIEWPORT_MAX && y > VIEWPORT_MIN){
                // if mouse is inside of viewport, clicking left button will 
                // spin the polygon counter-clockwise
                DELTA_SPIN = DELTA_SPIN - 1.0;
                glutIdleFunc(SpinDisplay);
            }
            else if(x > VIEWPORT_MAX || x < VIEWPORT_MIN || y > VIEWPORT_MAX || y < VIEWPORT_MIN){
                // if the mouse is outside of the viewport,
                // clicking the left button will increase the
                // factor of the polygon
                scalex += 0.05;
                scaley += 0.05;
                scalez += 0.05; 
                //increase scale
            }
            break;
        case GLUT_RIGHT_BUTTON:
            if (state == GLUT_DOWN && x < VIEWPORT_MAX && x > VIEWPORT_MIN && y < VIEWPORT_MAX && y > VIEWPORT_MIN){
                // if mouse is inside of viewport, clicking right button will 
                // spin the polygon clockwise
                DELTA_SPIN = DELTA_SPIN + 1.0;
                glutIdleFunc(SpinDisplay);
            }
            else if((x > VIEWPORT_MAX || x < VIEWPORT_MIN || y > VIEWPORT_MAX || y < VIEWPORT_MIN) && scalex >= 0.0){
                // if the mouse is outside of the viewport,
                // clicking the right button will decrease the
                // factor of the polygon               
                scalex -= 0.05;
                scaley -= 0.05;
                scalez -= 0.05;
                //decrease scale
            }
            break;
        default:
            break;
    }
}

