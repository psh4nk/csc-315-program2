#include "pipeline.c"
#include "includes.h"

void defineTree( float *apts ){
    // Defines the tree using a vector
    // and inputs the points into a 
    // float array

    float r = 200;
    float x,y;
    float TPI = 2 * M_PI;

    // input the tree coordinates into the tree vector
    if(count == 0){
        count++;
        tree.push_back({200,400,0,1});
        tree.push_back({725,450,0,1});
        for (float i = TPI/2; i >=0; i -= 0.001){
            x = (sin(i)*r)+650;
            y = (cos(i)*r)+500;
            tree.push_back({x,y,0,1});
        }
        tree.push_back({725,550,0,1});
        tree.push_back({200,600,0,1});
    }
    // convert the tree vector to a c array
    int vertmin = 0;
    for(int i = 0; i < tree.size(); i++){
        apts[vertmin] = tree[i].x;
        apts[vertmin+1] = tree[i].y;
        apts[vertmin+2] = tree[i].z;
        apts[vertmin+3] = tree[i].w;
        vertmin+=4;
    }
}

void toVertex ( float *apts, struct vertex *vp, int pts ){    
    //convert the c array containing the tree 
    //coordinates to a vertex array
    
    for (int i=0;i<pts;i++)
    {
        (vp+i)->x = *(apts+(i*4)+0);
        (vp+i)->y = *(apts+(i*4)+1);
        (vp+i)->z = *(apts+(i*4)+2);
        (vp+i)->w = *(apts+(i+4)+3);
    }
}


void drawTree( vertex *vp, int points ){
    // Draws the tree polygon onto the screen
    // Also calls the clipping routine before drawing

    // define window boundaries
    vertex left[2],top[2],right[2],bottom[2];
    left[0] = {100,900,0,1};
    left[1] = {100,100,0,1};
    top[0] = {900,900,0,1};
    top[1] = {100,900,0,1};
    right[0] = {900,100,0,1};
    right[1] = {900,900,0,1};
    bottom[0] = {100,100,0,1};
    bottom[1] = {900,100,0,1};

   
    // define some variables used for the clipping routine
    int j;
    int* outLength;
    outLength = &j;
    vertex *temp=vp;
    
    //for every point in the clipped tree,
    //check if any point goes outside the 
    //defined boundaries
    for(int i = 0; i < *outLength; i++){
        if(!Inside(*(vp+i),left))
            SutherlandHodgmanPolygonClip(vp,temp,points,outLength,left);
        if(!Inside(*(vp+i), bottom))
            SutherlandHodgmanPolygonClip(vp,temp,points,outLength,bottom);
        if(!Inside(*(vp+i), right))
            SutherlandHodgmanPolygonClip(vp,temp,points,outLength,right); 
        if(!Inside(*(vp+i), top))    
            SutherlandHodgmanPolygonClip(vp,temp,points,outLength,top);
    }

    //draw the clipped tree
    glBegin(GL_LINE_LOOP);
    for (int i=0;i<*outLength;i++){
        glVertex2f( (temp+i)->x, (temp+i)->y ); 
    }
    glEnd();
}

void fillTree(float *apts, int points){
    //tesselation goes here
    checkintersection(apts,points);
    glBegin(GL_TRIANGLE_FAN);
    std::cout<<"filling\n";
    for(int i = 0; i < triangles.size(); i+=3){
        glVertex2f(triangles[i].a[0], triangles[i].a[1]);
        glVertex2f(triangles[i+1].a[0], triangles[i+1].a[1]);
        glVertex2f(triangles[i+2].a[0], triangles[i+2].a[1]);
    }
    glEnd();
}                               
