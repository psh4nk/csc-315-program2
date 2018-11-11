//tessellate
//
//
#include "intersect.c"

void tessellate(){
    // Draws the triangles from the triangle vector on the screen
    
    glBegin(GL_LINES);  
    for(int i = 0; i < triangles.size(); i++){
        glVertex2f(triangles[i].a[0], triangles[i].a[1]);
        glVertex2f(triangles[i].c[0], triangles[i].c[1]);
        glVertex2f(triangles[i].b[0], triangles[i].b[1]); 
        double area = (.5*((triangles[i].a[0]*triangles[i].b[1]) + (triangles[i].b[0]*triangles[i].c[1]) + (triangles[i].c[0]*triangles[i].a[1]) -
                    (triangles[i].a[0]*triangles[i].c[1]) - (triangles[i].b[0]*triangles[i].a[1]) - (triangles[i].c[0]*triangles[i].b[1])));
    }     
    glEnd();
    glFlush();


}


