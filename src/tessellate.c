//tessellate
//
//
#include "intersect.c"

void tessellate(){
    // Draws the triangles from the triangle vector on the screen

    //glClearColor(1.0f, 1.0f, 1.0f, 1.0f );
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBegin(GL_LINE_LOOP);  
    for(int i = 0; i < triangles.size(); i++){
        glVertex2f(triangles[i].a[0], triangles[i].a[1]);
        glVertex2f(triangles[i].c[0], triangles[i].c[1]);
        glVertex2f(triangles[i].b[0], triangles[i].b[1]); 
        double area = (.5*((triangles[i].a[0]*triangles[i].b[1]) + (triangles[i].b[0]*triangles[i].c[1]) + (triangles[i].c[0]*triangles[i].a[1]) -
                    (triangles[i].a[0]*triangles[i].c[1]) - (triangles[i].b[0]*triangles[i].a[1]) - (triangles[i].c[0]*triangles[i].b[1])));
        std::cout<<"T" << i+1 << " area = " << area << '\n';
    }    
    std::cout<<"LKJSDFLKJSDFL:JKSDLJKSDFJKL\n";
    glEnd();
    //glFlush();


}


