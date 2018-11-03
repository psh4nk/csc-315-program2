#include "mouse.c"

void moveup(){
    movey += 5;
}

void movedown(){
    movey -= 5;
}

void moveleft(){
    movex -= 5;
}

void moveright(){
    movex += 5;
}

void SpecialInput(int key, int x, int y){
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

