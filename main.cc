//Preston Shankle
//
//
//

#include "init.c"
#include "keyboard.c"

int main(int argc, char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB); 
    glutInitWindowSize(WINDOW_MAX,WINDOW_MAX); 
    glutInitWindowPosition(0,0); 
    glutCreateWindow("The Arrow"); 
    myinit(); 
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(SpecialInput);
    glutDisplayFunc(display); 
    glutMainLoop();
}
