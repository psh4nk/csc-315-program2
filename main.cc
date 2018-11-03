// Preston Shankle
// main.cc
// November 6, 2018

#include "specialinput.c"
#include "init.c"

int main(int argc, char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB); 
    glutInitWindowSize(WINDOW_MAX,WINDOW_MAX); 
    glutInitWindowPosition(0,0); 
    glutCreateWindow("The Tree"); 
    myinit(); 
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(SpecialInput);
    glutDisplayFunc(display); 
    glutMainLoop();
}
