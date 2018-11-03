#include "display.c"

void SpinDisplay(void){
    SPIN = SPIN + DELTA_SPIN;
    if (SPIN > 360.0) SPIN = SPIN - 360.0;
    glutPostRedisplay();
}


void mouse(int button, int state, int x, int y) { 
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
                //decrease scale
            }
            break;
        default:
            break;
    }
}

