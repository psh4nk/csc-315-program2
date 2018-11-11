#include "keyboard.c"

void SpecialInput(int key, int x, int y){
    // Allows for input of the arrow keys,
    // which control the movement of the polygon
    
    switch(key){
        case GLUT_KEY_UP:
            moveup();
            break;
        case GLUT_KEY_DOWN:
            movedown();
            break;
        case GLUT_KEY_LEFT:
            moveleft();
            break;
        case GLUT_KEY_RIGHT:
            moveright();
            break;
        default:
            break;
    }
}

